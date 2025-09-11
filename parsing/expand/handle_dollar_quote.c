/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:42:26 by abdo              #+#    #+#             */
/*   Updated: 2025/09/11 15:26:14 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*copy_escapes(const char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			new_str[j++] = 1;
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*extract_dollar_quote(const char *str)
{
	char	quote;
	int		i;
	int		len;
	char	*res;
	int		j;

	quote = str[1];
	i = 2;
	len = 0;
	while (str[i + len] && str[i + len] != quote)
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
	{
		res[j] = str[i + j];
		j++;
	}
	res[len] = '\0';
	return (res);
}

char	*t_handle_dollar_quote(const char *str)
{
	if (str[0] == '$' && (str[1] == '\'' || str[1] == '"'))
		return (extract_dollar_quote(str));
	return (NULL);
}

void	handle_plain_char(const char *input, t_fir_expand_elements *st)
{
	st->result = expand_char_literal(st, input[st->i]);
	st->i++;
}
