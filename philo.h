/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebakirog <ebakirog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:41:01 by ebakirog          #+#    #+#             */
/*   Updated: 2024/02/07 23:19:57 by ebakirog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RESET "\033[0m"
# define GREEN "\033[1;32m"
# define WHITE "\033[1;37m"
# define YELLOW "\033[1;3;33m"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	int				eat;
	pthread_t		thread;
	struct s_table	*table;
	bool			self_fork;
	bool 			*other_fork;
}					t_philo;

typedef struct s_table
{
	int				d_time;
	int				e_time;
	int				s_time;
	int				p_count;
	int				e_count;
	long long		start;
	t_philo			*philo;
	pthread_mutex_t	mutex;
}					t_table;

int					ft_atoi(char *str);
void				error_msg(char *str);
int					check_all(char **av, int count);
void				assign_arg(char **av, int count, t_table *tab);
long long			get_time(void);
int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int 				is_thinking(t_philo *philo);
#endif