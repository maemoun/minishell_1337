/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:53:14 by abdo              #+#    #+#             */
/*   Updated: 2025/09/11 15:26:01 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*preprocess_escapes(const char *str)
{
	return (copy_escapes(str));
}

char	*strip_quotes(const char	*str)
{
	size_t	len;

	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
		return (ft_strndup(str + 1, len - 2));
	return (ft_strdup(str));
}

char	*preprocess_token(const char *str, char quote_type)
{
	char	*res;
	size_t	i;

	res = ft_strndup("", 0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$' && quote_type != '\'')
		{
			res = append_char(res, '$');
			i += 2;
		}
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

static void	expand_single_token(t_token *curr, t_data *dt, t_env *env)
{
	size_t	i;
	char	*tmp;
	char	*clean;
	char	*preprocessed;
	char	*expanded;

	tmp = t_handle_dollar_quote(curr->value);
	if (tmp)
	{
		free(curr->value);
		curr->value = tmp;
		return ;
	}
	clean = strip_quotes(curr->value);
	preprocessed = preprocess_token(clean, curr->value[0]);
	free(clean);
	i = 1;
	while (preprocessed[i] && ft_isspace(preprocessed[i]))
		i++;
	if (preprocessed[0] == '$' && i == ft_strlen(preprocessed))
		expanded = ft_strdup("$");
	else
		expanded = expand_var(preprocessed, dt, env);
	free_4(preprocessed, curr->value, NULL, NULL);
	curr->value = expanded;
}

void	expand_tokens(t_token	**tokens, t_data *dt, t_env *env)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (prev && prev->type == HEREDOC)
		{
			prev = curr;
			curr = curr->next;
			continue ;
		}
		if (!is_single_quoted(curr->value))
			expand_single_token(curr, dt, env);
		prev = curr;
		curr = curr->next;
	}
}
