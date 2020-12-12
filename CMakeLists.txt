# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbach <cbach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/06 13:00:09 by cbach             #+#    #+#              #
#    Updated: 2020/12/06 13:00:10 by cbach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

project(minishell)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-D BUFFER_SIZE=128")

#Utils sources
file(GLOB gnl "./get_next_line/*.c")
file(GLOB libft "./libft/*.c")

#Main sources
file(GLOB srcs "*.c")

#Parser sources
file(GLOB parser "./parser/*.c")


#Executor sources
file(GLOB executor "./executor/*.c")
file(GLOB exec_cmds "./executor/cmds/*.c")
file(GLOB exec_utils "./executor/utils/*.c")

#Utils headers
include_directories(libft/)
include_directories(get_next_line/)

#Parser headers
include_directories(parser/)

#Executor headers
include_directories(executor/)
include_directories(executor/utils)
include_directories(executor/cmds)

#System headers
include_directories(/usr/local/include)

add_executable(minishell ${srcs} ${gnl} ${executor}
        ${parser} ${libft} ${exec_cmds} ${exec_utils} )
