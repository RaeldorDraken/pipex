/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexlib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:46:43 by eros-gir          #+#    #+#             */
/*   Updated: 2022/07/23 14:28:49 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXLIB_H
# define PIPEXLIB_H

# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>
# include<sys/wait.h>
# include<stdio.h>
# include<errno.h>
# include"../libft/libft.h"

typedef struct s_pipex {
	int		infile;
	int		outfile;
	char	**command1;
	char	**command2;
	char	**paths;
	int		end[2];
}	t_pipex;

void	close_fds(t_pipex *pobj);
char	*final_path(char **paths, char *cmd);
void	cmd_error(char **cmd);
void	error_terminate(char *e, t_pipex *pobj);
void	argerror(int ac);
void	parse(t_pipex *pobj, char **envp, char **av);
char	*get_path_line(char **envp);
char	**ft_psplit(const char *s, char c, t_pipex *pobj, int quotes);
int		ft_check_quotes(char c);
void	ft_string_error(char **strings, size_t n, t_pipex *pobj);
void	set_vars(size_t *len, size_t *num, int *quotes);
size_t	add_numb(int quotes);
char	*ft_pscript(const char *s);
#endif
