#!/bin/bash

# ============================================
# CUB3D VALID MAPS TESTER
# ============================================

# CORES
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

# CONFIGURAÇÕES
CUB3D="./cub3D"
MAPS_DIR="./maps/maps_valid"
TIMEOUT=1.5  # Tempo em segundos antes de matar o processo

# CONTADORES
PASSED=0
FAILED=0
TOTAL=0

declare -a FAILED_MAPS

# ============================================
# FUNÇÃO DE TESTE
# ============================================
test_valid_map() {
    local map="$1"
    TOTAL=$((TOTAL + 1))
    
    filename=$(basename "$map")
    printf "[%3d] %-45s " "$TOTAL" "$filename"
    
    # Executa em background e captura PID
    $CUB3D "$map" &>/tmp/cub3d_output_$$ &
    local pid=$!
    
    # Aguarda um pouco para ver se abre a janela
    sleep $TIMEOUT
    
    # Verifica se o processo ainda está rodando
    if ps -p $pid > /dev/null 2>&1; then
        # Processo rodando = mapa válido, janela aberta
        echo -e "${GREEN}✓ VALID${NC} ${BLUE}(window opened successfully)${NC}"
        PASSED=$((PASSED + 1))
        
        # Mata o processo
        kill -9 $pid 2>/dev/null
        wait $pid 2>/dev/null
    else
        # Processo morreu = teve erro
        wait $pid 2>/dev/null
        exit_code=$?
        
        # Captura possível saída de erro
        error_output=$(cat /tmp/cub3d_output_$$ 2>/dev/null | grep -i "error" | head -1)
        
        if [ -n "$error_output" ]; then
            echo -e "${RED}✗ FAILED${NC} ${MAGENTA}→ $error_output${NC}"
        else
            echo -e "${RED}✗ FAILED${NC} ${MAGENTA}→ Process crashed (exit code: $exit_code)${NC}"
        fi
        
        FAILED=$((FAILED + 1))
        FAILED_MAPS+=("$filename|$error_output")
    fi
    
    # Limpa arquivo temporário
    rm -f /tmp/cub3d_output_$$
}

# ============================================
# INÍCIO DO SCRIPT
# ============================================

clear

if [ ! -f "$CUB3D" ]; then
    echo -e "${RED}Erro: $CUB3D não encontrado!${NC}"
    echo -e "${YELLOW}Compile primeiro: make${NC}"
    exit 1
fi

if [ ! -d "$MAPS_DIR" ]; then
    echo -e "${RED}Erro: Diretório $MAPS_DIR não encontrado!${NC}"
    exit 1
fi

echo -e "${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║            CUB3D VALID MAPS TESTER                       ║${NC}"
echo -e "${CYAN}║       (Auto-closes after ${TIMEOUT}s for valid maps)              ║${NC}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"
echo ""

# ============================================
# TESTA TODOS OS MAPAS VÁLIDOS
# ============================================

map_count=$(find "$MAPS_DIR" -name "*.cub" | wc -l)
echo -e "${YELLOW}Found $map_count maps in $MAPS_DIR${NC}\n"

for map in "$MAPS_DIR"/*.cub; do
    [ -f "$map" ] && test_valid_map "$map"
done

# ============================================
# RESUMO
# ============================================
echo -e "\n${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║                       SUMMARY                            ║${NC}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"

percentage=0
[ $TOTAL -gt 0 ] && percentage=$((PASSED * 100 / TOTAL))

echo -e "Total maps tested: ${YELLOW}$TOTAL${NC}"
echo -e "Valid (passed):    ${GREEN}$PASSED${NC}"
echo -e "Invalid (failed):  ${RED}$FAILED${NC}"
echo -e "Success rate:      ${YELLOW}$percentage%${NC}"

# ============================================
# DETALHES DOS MAPAS QUE FALHARAM
# ============================================
if [ $FAILED -gt 0 ]; then
    echo -e "\n${RED}╔══════════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║                  ⚠️  FAILED MAPS  ⚠️                      ║${NC}"
    echo -e "${RED}╚══════════════════════════════════════════════════════════╝${NC}"
    
    count=1
    for entry in "${FAILED_MAPS[@]}"; do
        IFS='|' read -r filename error <<< "$entry"
        
        echo -e "\n${MAGENTA}[$count] $filename${NC}"
        if [ -n "$error" ]; then
            echo -e "    Error: ${RED}$error${NC}"
        else
            echo -e "    ${RED}Process crashed without error message${NC}"
        fi
        echo -e "    ${BLUE}────────────────────────────────────────────────${NC}"
        
        count=$((count + 1))
    done
    
    echo -e "\n${YELLOW}💡 Tip: Run failed maps manually to debug:${NC}"
    echo -e "   ${CYAN}./cub3D $MAPS_DIR/map_name.cub${NC}\n"
    
    exit 1
else
    echo -e "\n${GREEN}╔══════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║          🎉 ALL VALID MAPS PASSED! 🎉                    ║${NC}"
    echo -e "${GREEN}╚══════════════════════════════════════════════════════════╝${NC}\n"
    exit 0
fi
