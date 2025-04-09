#include <stdlib.h>
#include <unistd.h>
// do we have to update the path name before the semicolon??
/*
Symbolic Links (Symlinks): Unlike hard links, symlinks are independent files 
that store a pointer to the target. They can cross filesystems and can 
reference directories.
A symlink is a file that contains a path (either relative or absolute) 
to another file or directory. When you access the symlink, 
the operating system automatically redirects you to the target file or 
directory.
t’s similar to a shortcut in Windows, but at the filesystem level.

*/
typedef struct s_env_vars 
{
    char *key;
    char *value;
    struct s_env_vars *next;
} t_env_vars;

int skip_cd_cmd(const char *input)
{
    int i = 0;
    //do we need all space chars?? 
    while (input[i] == ' ' || input[i] == '\t')
        i++;

    // Skip 'cd'
    if (input[i] == 'c' && input[i + 1] == 'd') {
        i += 2;
    } else {
        return i; // not a valid cd command, but we'll be defensive
    }

// Skip whitespace after 'cd'
 while (input[i] == ' ' || input[i] == '\t')
        i++;

    return i;
}

int ft_strcmp(const char *s1, const char *s2) 
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    
    return (unsigned char)*s1 - (unsigned char)*s2;
}

t_env_vars *get_env_node(t_env_vars *head, const char *key) {
    while (head) {
        if (ft_strcmp(head->key, key) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

char *ft_strdup(const char *s) 
{
    size_t len = 0;
    const char *p = s;
   
    while (*p++) {
        len++;
    }
   
    char *dup = malloc(len + 1);
    if (!dup) {
        return NULL; 
    }
    
    for (size_t i = 0; i <= len; i++) {
        dup[i] = s[i]; 
    }
    
    return dup;
}


void set_env_var(t_env_vars **head, const char *key, const char *value) {
    t_env_vars *node = get_env_node(*head, key);

    if (node) {
        free(node->value);
        node->value = ft_strdup(value);
    } else {
        node = malloc(sizeof(t_env_vars));
        node->key = ft_strdup(key);
        node->value = ft_strdup(value);
        node->next = *head;
        *head = node;
    }
}


//ptr to head of list hence double ptr
void ft_cd(char *input, t_env_vars **env_list)
{
 char old_pwd[10000];
    char new_pwd[10000];
    char *target_path = NULL;
    int i = skip_cd_cmd(input);

    // Get current dir first (for OLDPWD)
    if (!getcwd(old_pwd, sizeof(old_pwd))) {
        printf("cd: getcwd");
        return;
    }

    // Handle special cases (~, -, no arg or . .. )???
   // if (input[i] == '\0' || input[i] == '~' || input[i] == '-') {
    
    //}

    //chdir interprets it relative to the current working directory so works for both rel/abs
    if (chdir(target_path) == -1) {
        printf("cd");
        return;
    }

    if (!getcwd(new_pwd, sizeof(new_pwd))) {
        printf("cd: getcwd");

        return;
    }

    set_env_var(env_list, "OLDPWD", old_pwd);
    set_env_var(env_list, "PWD", new_pwd);


}