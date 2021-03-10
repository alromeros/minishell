/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalazon <cpalazon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:12:13 by cpalazon          #+#    #+#             */
/*   Updated: 2020/02/12 12:37:31 by cpalazon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"

int		get_next_line(char **line);

#endif
