#! /bin/bash

echo -n "uninstall chain reaction game? [y/n]: "
read answer
if [ $answer == 'y' ]
then
	echo "removing shortcuts if any..."
	if [ -f /usr/bin/chain ]
	then
		rm /usr/bin/chain
	fi
	if [ -d ~/.local/bin/ ]
	then
		if [ -f ~/.local/bin/chain ]
		then
			rm ~/.local/bin/chain
		fi
	fi
	echo "removing desktop files..."
	rm -f start.desktop
	rm -f ~/.local/share/applications/start.desktop
	echo "removing supporting utilities..."
	rm -f -r ~/.chainreaction
	rm chain
	echo "successfully uninstalled chain reaction game"
	echo "to reinstall, run make.sh file again"
else
	echo "uninstall cancelled"
fi
