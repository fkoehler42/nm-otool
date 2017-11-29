#! /bin/bash

vimdiff <(./ft_nm $@) <(nm $@)
