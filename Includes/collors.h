/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:29:34 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/11 22:48:35 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLORS_H
# define COLLORS_H

// Regular Colors
#define COLOR_RED    0xFF0000
#define COLOR_GREEN  0x00FF00
#define COLOR_BLUE   0x0000FF
#define COLOR_YELLOW 0xFFFF00
#define COLOR_VERT_RAY   0xFF00FF  // Magenta for vertical rays
#define COLOR_HORIZ_RAY  0x00FFFF  // Cyan for horizontal rays

// Bold Colors
# define COLOR_BOLD_BLACK "\033[1;30m"
# define COLOR_BOLD_RED "\033[1;31m"
# define COLOR_BOLD_GREEN "\033[1;32m"
# define COLOR_BOLD_YELLOW "\033[1;33m"
# define COLOR_BOLD_BLUE "\033[1;34m"
# define COLOR_BOLD_MAGENTA "\033[1;35m"
# define COLOR_BOLD_CYAN "\033[1;36m"
# define COLOR_BOLD_WHITE "\033[1;37m"

// Background Colors
# define COLOR_BG_BLACK "\033[0;40m"
# define COLOR_BG_RED "\033[0;41m"
# define COLOR_BG_GREEN "\033[0;42m"
# define COLOR_BG_YELLOW "\033[0;43m"
# define COLOR_BG_BLUE "\033[0;44m"
# define COLOR_BG_MAGENTA "\033[0;45m"
# define COLOR_BG_CYAN "\033[0;46m"
# define COLOR_BG_WHITE "\033[0;47m"

// Reset Color
# define COLOR_RESET "\033[0m"
#endif