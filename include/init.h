/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:33 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:22:34 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
#define INIT_H

struct s_simulation;
struct s_args;

int init_simulation(struct s_simulation *sim, struct s_args *args);
int init_coders(struct s_simulation *sim);
int init_dongles(struct s_simulation *sim);
int init_monitor(struct s_simulation *sim);

void destroy_simulation(struct s_simulation *sim);

#endif
