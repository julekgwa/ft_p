//
// Created by Junius LEKGWARA on 2017/07/10.
//

#include "minishell.h"

int main(int ac, char **av, char **envp) {
    char **sp = SPLIT("/bin/ls includes", ' ');
    ft_execute_cmd(sp[0], sp, envp);
    return  0;
}