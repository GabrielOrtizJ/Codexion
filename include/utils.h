/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:41 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 11:50:50 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

long	ft_atoll_strict(const char *str);
int		is_number(const char *str);
void	error_exit(const char *msg);
long	time_ms(void);
long	timestamp_ms(void);

#endif
