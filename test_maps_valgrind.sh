#!/bin/bash

# ============================================
# CUB3D TESTER - VERSÃO COM VALGRIND
# ============================================

# CORES
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# CONFIGURAÇÕES
CUB3D="./cub3D"
MAPS_VALID="./maps/maps_valid"
MAPS_INVALID="./maps/maps_invalid"
USE_VALGRIND=true  # Mude para false se quiser desabilitar

# CONTADORES
PASSED=0
FAILED=0
TOTAL=0
LEAKS=0

# Arrays para guardar resultados
declare -a FAILED_MAPS
declare -a LEAK_MAPS

# ============================================
# FUNÇÃO DE TESTE
# ============================================
test_map() {
    local map="$1"
    local expected="$2"
    
    TOTAL=$((TOTAL + 1))
    
    filename=$(basename "$map")
    printf "[%3d] %-40s " "$TOTAL" "$filename"
    
    # Executa com ou sem valgrind
    if [ "$USE_VALGRIND" = true ]; then
        # Valgrind com timeout de 3 segundos
        valgrind_output=$(timeout 3s valgrind --leak-check=full --errors-for-leak-kinds=all \
                         --show-leak-kinds=all --track-origins=yes --error-exitcode=42 \
                         "$CUB3D" "$map" 2>&1)
        exit_code=$?
        
        # Verifica se teve leak
        has_leak=$(echo "$valgrind_output" | grep -c "definitely lost\|indirectly lost\|possibly lost")
        
        # Pega a saída do programa (sem o valgrind)
        output=$(echo "$valgrind_output" | grep -v "^==" | grep -v "^--")
        has_error=$(echo "$output" | grep -ic "error")
        
        # Extrai resumo de leaks
        leak_summary=$(echo "$valgrind_output" | grep "definitely lost" | head -1)
        
    else
        # Executa sem valgrind
        output=$(timeout 3s "$CUB3D" "$map" 2>&1)
        exit_code=$?
        has_error=$(echo "$output" | grep -ic "error")
        has_leak=0
    fi
    
    # Verifica timeout
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}✗ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
        FAILED_MAPS+=("$filename|timeout|Program took too long")
        return
    fi
    
    # Testa se é válido ou inválido
    if [ "$expected" = "valid" ]; then
        if [ $has_error -eq 0 ]; then
            if [ $has_leak -gt 0 ]; then
                echo -e "${YELLOW}⚠ LEAK${NC}"
                LEAKS=$((LEAKS + 1))
                LEAK_MAPS+=("$filename|$leak_summary")
            else
                echo -e "${GREEN}✓ PASS${NC}"
                PASSED=$((PASSED + 1))
            fi
        else
            echo -e "${RED}✗ FAIL${NC} (should be valid)"
            FAILED=$((FAILED + 1))
            FAILED_MAPS+=("$filename|valid|$output")
        fi
    else
        if [ $has_error -gt 0 ]; then
            first_error=$(echo "$output" | grep -i "error" | head -1 | sed 's/^[[:space:]]*//')
            
            if [ $has_leak -gt 0 ]; then
                echo -e "${YELLOW}⚠ LEAK${NC} ${MAGENTA}→ $first_error${NC}"
                LEAKS=$((LEAKS + 1))
                LEAK_MAPS+=("$filename|$leak_summary")
            else
                echo -e "${GREEN}✓ PASS${NC} ${MAGENTA}→ $first_error${NC}"
                PASSED=$((PASSED + 1))
            fi
        else
            echo -e "${RED}✗ FAIL${NC} (should have error)"
            FAILED=$((FAILED + 1))
            FAILED_MAPS+=("$filename|invalid|No error detected")
        fi
    fi
}

# ============================================
# INÍCIO DO SCRIPT
# ============================================

clear

# Verifica se valgrind está instalado
if [ "$USE_VALGRIND" = true ]; then
    if ! command -v valgrind &> /dev/null; then
        echo -e "${RED}Erro: Valgrind não está instalado!${NC}"
        echo -e "${YELLOW}Instale com: sudo apt install valgrind${NC}"
        exit 1
    fi
fi

if [ ! -f "$CUB3D" ]; then
    echo -e "${RED}Erro: $CUB3D não encontrado!${NC}"
    exit 1
fi

echo -e "${CYAN}╔════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║         CUB3D MAP TESTER WITH VALGRIND             ║${NC}"
echo -e "${CYAN}╚════════════════════════════════════════════════════╝${NC}"

if [ "$USE_VALGRIND" = true ]; then
    echo -e "${YELLOW}Running with Valgrind (leak detection enabled)${NC}"
else
    echo -e "${YELLOW}Running without Valgrind${NC}"
fi
echo ""

# ============================================
# TESTA MAPAS VÁLIDOS
# ============================================
echo -e "${YELLOW}═══ VALID MAPS ═══${NC}"

if [ -d "$MAPS_VALID" ]; then
    for map in "$MAPS_VALID"/*.cub; do
        [ -f "$map" ] && test_map "$map" "valid"
    done
else
    echo -e "${RED}Pasta $MAPS_VALID não encontrada!${NC}"
fi

# ============================================
# TESTA MAPAS INVÁLIDOS
# ============================================
echo -e "\n${YELLOW}═══ INVALID MAPS ═══${NC}"

if [ -d "$MAPS_INVALID" ]; then
    for map in "$MAPS_INVALID"/*.cub "$MAPS_INVALID"/*.ber; do
        [ -f "$map" ] && test_map "$map" "invalid"
    done
else
    echo -e "${RED}Pasta $MAPS_INVALID não encontrada!${NC}"
fi

# ============================================
# RESUMO
# ============================================
echo -e "\n${CYAN}╔════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║                    SUMMARY                         ║${NC}"
echo -e "${CYAN}╚════════════════════════════════════════════════════╝${NC}"

percentage=0
[ $TOTAL -gt 0 ] && percentage=$((PASSED * 100 / TOTAL))

echo -e "Total tests:  ${YELLOW}$TOTAL${NC}"
echo -e "Passed:       ${GREEN}$PASSED${NC}"
echo -e "Failed:       ${RED}$FAILED${NC}"
echo -e "Leaks:        ${YELLOW}$LEAKS${NC}"
echo -e "Success rate: ${YELLOW}$percentage%${NC}"

# ============================================
# MOSTRA DETALHES DOS LEAKS
# ============================================
if [ $LEAKS -gt 0 ]; then
    echo -e "\n${YELLOW}╔════════════════════════════════════════════════════╗${NC}"
    echo -e "${YELLOW}║              ⚠ MEMORY LEAKS DETECTED ⚠             ║${NC}"
    echo -e "${YELLOW}╚════════════════════════════════════════════════════╝${NC}"
    
    count=1
    for entry in "${LEAK_MAPS[@]}"; do
        IFS='|' read -r filename leak_info <<< "$entry"
        
        echo -e "\n${MAGENTA}[$count] $filename${NC}"
        echo -e "    ${RED}$leak_info${NC}"
        
        count=$((count + 1))
    done
fi

# ============================================
# MOSTRA DETALHES DOS ERROS
# ============================================
if [ $FAILED -gt 0 ]; then
    echo -e "\n${RED}╔════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              ❌ FAILED TESTS DETAILS ❌             ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════╝${NC}"
    
    count=1
    for entry in "${FAILED_MAPS[@]}"; do
        IFS='|' read -r filename expected error <<< "$entry"
        
        echo -e "\n${MAGENTA}[$count] $filename${NC}"
        echo -e "    Expected: ${YELLOW}$expected${NC}"
        echo -e "    Error: ${RED}$error${NC}"
        echo -e "    ${BLUE}────────────────────────────────────────────${NC}"
        
        count=$((count + 1))
    done
fi

# ============================================
# RESULTADO FINAL
# ============================================
echo ""
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}❌ $FAILED TESTS FAILED ❌${NC}\n"
    exit 1
elif [ $LEAKS -gt 0 ]; then
    echo -e "${YELLOW}⚠ ALL TESTS PASSED BUT $LEAKS MEMORY LEAKS DETECTED ⚠${NC}\n"
    exit 1
else
    echo -e "${GREEN}╔════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║    🎉 ALL TESTS PASSED WITHOUT LEAKS! 🎉          ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════╝${NC}\n"
    exit 0
fi
