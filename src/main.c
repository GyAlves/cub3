/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:01:01 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/06 19:43:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

int main(int argc, char **argv)
{
    t_game game;
    
    // jucoelho
    if (parse_file(argv[1], &game) != 0)
        return (error_exit());
    
    // galves
    if (init_engine(&game) != 0)
        return (error_exit());
    
    // galves
    game_loop(&game);
    
    // galves
    cleanup_engine(&game);

    // ??
    free_game_data(&game);
    
    return (0);
}