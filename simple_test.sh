#!/bin/bash

# ============================================
# CUB3D TESTER - VERSÃO MELHORADA
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

# CONTADORES
PASSED=0
FAILED=0
TOTAL=0

# Array para guardar mapas que falharam
declare -a FAILED_MAPS

# ============================================
# FUNÇÃO DE TESTE
# ============================================
test_map() {
    local map="$1"
    local expected="$2"
    
    TOTAL=$((TOTAL + 1))
    
    # Executa e captura saída
    output=$($CUB3D "$map" 2>&1)
    has_error=$(echo "$output" | grep -ic "error")
    
    filename=$(basename "$map")
    
    # Linha mais curta e limpa
    printf "[%3d] %-40s " "$TOTAL" "$filename"
    
    if [ "$expected" = "valid" ]; then
        if [ $has_error -eq 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAIL${NC} (should be valid)"
            FAILED=$((FAILED + 1))
            FAILED_MAPS+=("$filename|valid|$output")
        fi
    else
        if [ $has_error -gt 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASSED=$((PASSED + 1))
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

if [ ! -f "$CUB3D" ]; then
    echo -e "${RED}Erro: $CUB3D não encontrado!${NC}"
    exit 1
fi

echo -e "${CYAN}╔════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║              CUB3D MAP TESTER                      ║${NC}"
echo -e "${CYAN}╚════════════════════════════════════════════════════╝${NC}"
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
echo -e "Success rate: ${YELLOW}$percentage%${NC}"

# ============================================
# MOSTRA DETALHES DOS ERROS
# ============================================
if [ $FAILED -gt 0 ]; then
    echo -e "\n${RED}╔════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              ❌ FAILED TESTS DETAILS ❌             ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════╝${NC}"
    
    count=1
    for entry in "${FAILED_MAPS[@]}"; do
        # Separa as partes
        IFS='|' read -r filename expected error <<< "$entry"
        
        echo -e "\n${MAGENTA}[$count] $filename${NC}"
        echo -e "    Expected: ${YELLOW}$expected${NC}"
        echo -e "    Error: ${RED}$error${NC}"
        echo -e "    ${BLUE}────────────────────────────────────────────${NC}"
        
        count=$((count + 1))
    done
    
    echo -e "\n${RED}❌ $FAILED TESTS FAILED ❌${NC}\n"
    exit 1
else
    echo -e "\n${GREEN}╔════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║          🎉 ALL TESTS PASSED! 🎉                   ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════╝${NC}\n"
    exit 0
fi