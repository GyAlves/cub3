/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"
#include <signal.h>

static t_game	*g_game_ptr = NULL;

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 * Cleans up resources and exits gracefully.
 *
 * @param sig Signal number (unused).
 */
static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_game_ptr)
	{
		ft_printf("\nCleaning up and exiting...\n");
		ft_free_game(g_game_ptr);
		gnl_cleanup();
	}
	exit(0);
}

/**
 * @brief Sets up signal handlers for graceful shutdown.
 *
 * @param game Pointer to the game structure.
 */
void	setup_signal_handlers(t_game *game)
{
	g_game_ptr = game;
	signal(SIGINT, handle_sigint);
}
