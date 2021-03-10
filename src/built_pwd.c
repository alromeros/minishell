/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:53:43 by alromero          #+#    #+#             */
/*   Updated: 2021/02/22 12:04:28 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, -1);
	write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
}
