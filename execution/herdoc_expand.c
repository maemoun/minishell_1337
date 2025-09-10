#include ".././parsing/main.h"

static void	handle_variable_herdoc(const char *input, t_fir_expand_elements *st)
{
	if (input[st->i + 1] == '?')
	{
		st->result = f_expand_exit_status(st);
		st->i += 2;
	}
	else if (ft_is_valid_var_char(input[st->i + 1]))
		expand_variable_name(input, st);
	else
	{
		st->result = ft_strjoin(st->result, "$");
		st->i++;
	}
}

char	*expand_var_herdoc(const char *input, t_env *env, int last_exit_status)
{
	t_fir_expand_elements	st;

	st.env = env;
	st.last_exit_status = last_exit_status;
	st.i = 0;
	st.in_single = 0;
	st.in_double = 0;
	st.result = ft_strndup("", 0);
	while (input[st.i])
	{
		if (input[st.i] == '\\' && input[st.i + 1] == '$' && !st.in_single)
			handle_escaped_dollar(input, &st);
		else if ((input[st.i] == '\'' && !st.in_double)
			|| (input[st.i] == '"' && !st.in_single))
			handle_quotes(input, &st);
		else if (input[st.i] == '$')
			handle_variable_herdoc(input, &st);
		else
			handle_plain_char(input, &st);
	}
	return (st.result);
}
