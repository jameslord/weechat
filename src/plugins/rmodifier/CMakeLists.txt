#
# Copyright (C) 2010-2012 Sebastien Helleu <flashcode@flashtux.org>
#
# This file is part of WeeChat, the extensible chat client.
#
# WeeChat is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# WeeChat is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with WeeChat.  If not, see <http://www.gnu.org/licenses/>.
#

ADD_LIBRARY(rmodifier MODULE
rmodifier.c rmodifier.h
rmodifier-command.c rmodifier-command.h
rmodifier-completion.c rmodifier-completion.h
rmodifier-config.c rmodifier-config.h
rmodifier-debug.c rmodifier-debug.h
rmodifier-info.c rmodifier-info.h)
SET_TARGET_PROPERTIES(rmodifier PROPERTIES PREFIX "")

TARGET_LINK_LIBRARIES(rmodifier)

INSTALL(TARGETS rmodifier LIBRARY DESTINATION ${LIBDIR}/plugins)
