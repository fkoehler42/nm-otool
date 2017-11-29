#! /bin/bash

vimdiff <(./ft_otool $@) <(otool $@)
