#!/bin/bash

(cd src && clang-format -n grep/grep.c)
(cd src && clang-format -n cat/cat.c)
(cd src && clang-format -n common/utils.*)