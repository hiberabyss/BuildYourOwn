#!/bin/bash
# Copyright (c) 2021, Soul Inc
# Author: Hongbo Liu <liulu3@soulapp.com>
# Date  : 2021-12-29 13:46:16

docker run -it -d --name bazel \
  --restart always \
  --network host \
  -w /code \
  -v `pwd`:/code -v $HOME/.cache/bazel:/root/.cache \
  hbliu/bazel
