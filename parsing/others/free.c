/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:30:41 by abdo              #+#    #+#             */
/*   Updated: 2025/09/11 14:47:26 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_redirections(t_redirection *red)
{
	t_redirection	*r_tmp;

	while (red)
	{
		r_tmp = red->next_red;
		free(red->name);
		free(red);
		red = r_tmp;
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next_command;
		if (cmd->command)
		{
			i = 0;
			while (cmd->command[i])
				free(cmd->command[i++]);
			free(cmd->command);
		}
		free_redirections(cmd->red);
		free(cmd);
		cmd = tmp;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_4(char *a, char *b, char *c, char *d)
{
	if (a)
	{
		free(a);
		a = NULL;
	}
	if (b)
	{
		free(b);
		b = NULL;
	}
	if (c)
	{
		free(c);
		c = NULL;
	}
	if (d)
	{
		free(d);
		d = NULL;
	}
}
