#include "mini.h"

void	ft_set_oldpwd_var(t_mini *mini, char cwd[100])
{
	char	pwd_var[200];
	char	*tmp;
	char	**args;

	tmp = NULL;
	args = NULL;
	ft_strcpy(pwd_var, "OLDPWD=");
	ft_strcat(pwd_var, cwd);
	tmp = ft_strjoin("export ", pwd_var);
	if (tmp)
	{
		args = ft_split(tmp, ' ');
		if (args)
		{
			ft_export(args, mini);
			ft_2dstrfree(args);
		}
		free(tmp);
	}
}

void	ft_set_pwd_var(t_mini *mini, char cwd[100])
{
	char	pwd_var[200];
	char	*tmp;
	char	**args;

	tmp = NULL;
	args = NULL;
	ft_strcpy(pwd_var, "PWD=");
	ft_strcat(pwd_var, cwd);
	tmp = ft_strjoin("export ", pwd_var);
	if (tmp)
	{
		args = ft_split(tmp, ' ');
		if (args)
		{
			ft_export(args, mini);
			ft_2dstrfree(args);
		}
		free(tmp);
	}
}

void	ft_pwd(t_mini *mini)
{
	char	cwd[100];

	getcwd(cwd, 100);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	mini->exit_status = 0;
}
