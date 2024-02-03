/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:50:56 by eros-gir          #+#    #+#             */
/*   Updated: 2022/07/23 14:41:50 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipexlib.h"

void	set_vars(size_t *len, size_t *num, int *quotes)
{
	*len = 0;
	*num = 0;
	*quotes = 0;
}

void	child1_process(t_pipex *pobj, char **envp)
{
	char	*cmd;

	close(pobj->end[0]);
	close(pobj->outfile);
	cmd = final_path(pobj->paths, pobj->command1[0]);
	dup2(pobj->infile, STDIN_FILENO);
	dup2(pobj->end[1], STDOUT_FILENO);
	if (cmd && pobj->command1[0])
	{
		execve(cmd, pobj->command1, envp);
		free(cmd);
	}
	else
	{
		free(cmd);
		cmd_error(pobj->command1);
	}
}

void	child2_process(t_pipex *pobj, char **envp)
{
	char	*cmd;

	close(pobj->end[1]);
	close(pobj->infile);
	cmd = final_path(pobj->paths, pobj->command2[0]);
	dup2(pobj->outfile, STDOUT_FILENO);
	dup2(pobj->end[0], STDIN_FILENO);
	if (cmd && pobj->command2[0])
	{
		execve(cmd, pobj->command2, envp);
		free(cmd);
	}
	else
	{
		free(cmd);
		cmd_error(pobj->command2);
	}
}

void	pipex(t_pipex *pobj, char **envp)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pobj->end) < 0)
		error_terminate("ERROR", pobj);
	if (pobj->infile >= 0)
	{
		child1 = fork();
		if (child1 < 0)
			error_terminate("fork", pobj);
		if (child1 == 0)
			child1_process(pobj, envp);
	}
	child2 = fork();
	if (child2 < 0)
		error_terminate("fork", pobj);
	if (child2 == 0)
		child2_process(pobj, envp);
	close_fds(pobj);
	if (pobj->infile >= 0)
		waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pobj;

	if (ac != 5)
		argerror(ac);
	parse(&pobj, envp, av);
	pipex(&pobj, envp);
	exit(EXIT_SUCCESS);
	return (0);
}
