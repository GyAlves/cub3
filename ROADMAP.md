# cub3D - Roadmap de Implementação

## Status Atual
- [x] Parsing do arquivo `.cub`
- [x] Validação do mapa (paredes fechadas, jogador único)
- [x] Carregamento de texturas (NO, SO, WE, EA)
- [x] Parsing de cores (Floor e Ceiling)
- [x] Criação da janela MLX
- [x] **Engine de Raycasting**
- [x] **Renderização**
- [x] **Controles do jogador**

---

## Fase 1: Estrutura Base do Game Loop

### 1.1 Criar imagem de buffer
```c
// Criar uma imagem para desenhar antes de exibir
game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
game->img_data = mlx_get_data_addr(game->img, &bpp, &line_len, &endian);
```

### 1.2 Implementar game loop
```c
mlx_loop_hook(game->mlx, render_frame, game);
mlx_loop(game->mlx);
```

### 1.3 Função para desenhar pixel
```c
void put_pixel(t_game *game, int x, int y, int color);
```

---

## Fase 2: Inicialização do Jogador

### 2.1 Configurar posição inicial
- Converter posição do mapa (grid) para coordenadas do mundo
- `pos_x` e `pos_y` = centro do tile inicial + 0.5

### 2.2 Configurar vetor de direção
| Direção | dir_x | dir_y | plane_x | plane_y |
|---------|-------|-------|---------|---------|
| N       | 0     | -1    | 0.66    | 0       |
| S       | 0     | 1     | -0.66   | 0       |
| E       | 1     | 0     | 0       | 0.66    |
| W       | -1    | 0     | 0       | -0.66   |

---

## Fase 3: Algoritmo de Raycasting (DDA)

### 3.1 Para cada coluna x da tela (0 até WIDTH):

```c
// 1. Calcular posição e direção do raio
double camera_x = 2 * x / (double)WIDTH - 1;
double ray_dir_x = dir_x + plane_x * camera_x;
double ray_dir_y = dir_y + plane_y * camera_x;

// 2. Calcular delta_dist (distância entre intersecções)
double delta_dist_x = fabs(1 / ray_dir_x);
double delta_dist_y = fabs(1 / ray_dir_y);

// 3. Calcular step e side_dist inicial
// 4. Executar DDA até encontrar parede
// 5. Calcular distância perpendicular
// 6. Calcular altura da linha na tela
```

### 3.2 Referência recomendada
- Tutorial Lodev: https://lodev.org/cgtutor/raycasting.html

---

## Fase 4: Renderização

### 4.1 Desenhar teto (metade superior)
- Usar `map->ceiling_color` para preencher de y=0 até drawStart

### 4.2 Desenhar parede com textura
```c
// Determinar qual textura usar baseado na direção da parede
// side == 0 && ray_dir_x > 0 → EA (Leste)
// side == 0 && ray_dir_x < 0 → WE (Oeste)
// side == 1 && ray_dir_y > 0 → SO (Sul)
// side == 1 && ray_dir_y < 0 → NO (Norte)

// Calcular coordenada X da textura
double wall_x; // onde exatamente a parede foi atingida
int tex_x = (int)(wall_x * tex_width);

// Para cada pixel Y da coluna, mapear para textura
```

### 4.3 Desenhar chão (metade inferior)
- Usar `map->floor_color` para preencher de drawEnd até HEIGHT

### 4.4 Exibir imagem
```c
mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
```

---

## Fase 5: Controles do Jogador

### 5.1 Movimentação (W, A, S, D)
```c
// W - Mover para frente
new_x = pos_x + dir_x * move_speed;
new_y = pos_y + dir_y * move_speed;

// S - Mover para trás
new_x = pos_x - dir_x * move_speed;
new_y = pos_y - dir_y * move_speed;

// A - Mover para esquerda (strafe)
new_x = pos_x - plane_x * move_speed;
new_y = pos_y - plane_y * move_speed;

// D - Mover para direita (strafe)
new_x = pos_x + plane_x * move_speed;
new_y = pos_y + plane_y * move_speed;
```

### 5.2 Rotação (Setas esquerda/direita)
```c
// Rotação usa matriz de rotação
double old_dir_x = dir_x;
dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);

double old_plane_x = plane_x;
plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
```

### 5.3 Hooks de teclado
```c
mlx_hook(game->win, 2, 1L<<0, key_press, game);   // KeyPress
mlx_hook(game->win, 3, 1L<<1, key_release, game); // KeyRelease
```

---

## Fase 6: Eventos de Saída

### 6.1 Tecla ESC
```c
if (keycode == 53 || keycode == 65307) // ESC (macOS / Linux)
    clean_exit(game);
```

### 6.2 Botão X da janela
```c
mlx_hook(game->win, 17, 0, close_window, game); // DestroyNotify
```

---

## Fase 7: Polimento

### 7.1 Checklist final
- [ ] Sem memory leaks (testar com valgrind/leaks)
- [ ] Sem crashes em mapas inválidos
- [ ] Texturas diferentes para cada direção
- [ ] Cores de chão e teto configuráveis
- [ ] Movimento suave (usar key states, não key events)
- [ ] Norminette passando

### 7.2 Testes recomendados
- Testar todos os mapas em `maps/maps_valid/`
- Testar todos os mapas em `maps/maps_invalid/` (devem retornar erro)
- Testar movimentação em mapas grandes
- Testar rotação 360°

---

## Bônus (Opcional)

Só implementar se a parte obrigatória estiver **perfeita**:

- [ ] Colisão com paredes
- [ ] Minimapa
- [ ] Portas que abrem/fecham
- [ ] Sprites animados
- [ ] Rotação com mouse

---

## Arquivos Sugeridos

```
src/
├── 01_parsing/          # ✅ Já implementado
├── 02_engine/
│   ├── raycasting.c     # Algoritmo DDA
│   ├── render.c         # Desenhar frame
│   └── textures.c       # Mapear texturas
├── 03_controls/
│   ├── movement.c       # WASD
│   ├── rotation.c       # Setas
│   └── hooks.c          # Event handlers
└── utils/
    ├── pixel.c          # put_pixel
    └── cleanup.c        # Free e exit
```

---

## Recursos Úteis

1. **Tutorial Lodev (essencial)**: https://lodev.org/cgtutor/raycasting.html
2. **Vídeo 3Blue1Brown**: https://www.youtube.com/watch?v=eOCQfxRQ2pY
3. **Wolfenstein 3D original**: http://users.atw.hu/wolf3d/
