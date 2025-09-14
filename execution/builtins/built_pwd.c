#include "../.././parsing/main.h"

int	ft_pwd(t_env *env_list)
{
	char	*pwd;

	pwd = get_value(env_list, "PWD");
	printf("1---->[%s]\n", pwd);
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		printf("2---->[%s]\n", pwd);
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", pwd);
	return (0);
}
