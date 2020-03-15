#! /bin/bash

echo "installing the game..."
make 
make clean 
echo -e "[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Name=Chain
Exec= gnome-terminal -- /bin/bash -c \"nohup ~/.chainreaction/chain --TTF_PATH ~/.chainreaction/font.ttf --SAVED_GAME_PATH ~/.chainreaction/ > /dev/null 2> /dev/null\"
StartupNotify = true" > start.desktop
chmod +x start.desktop
if [ -d ~/.local/share/applications ]
then
	echo "copying desktop file..."
	cp start.desktop ~/.local/share/applications/start.desktop
fi
echo -n "create a shortcut for game? [y/n]: "
read answer
if [ $answer == "y" ]
then
	echo "creating shortcut..."
	if [ -d ~/.local/bin ]
	then
		echo "#! /bin/bash" >> ~/.local/bin/chain
		echo "" >> ~/.local/bin/chain
		echo "~/.chainreaction/chain --TTF_PATH ~/.chainreaction/font.ttf --SAVED_GAME_PATH ~/.chainreaction/ \$*" >> ~/.local/bin/chain
		chmod +x ~/.local/bin/chain
	else
		echo "#! /bin/bash" >> /usr/bin/chain
		echo "" >> /usr/bin/chain
		echo "~/.chainreaction/chain --TTF_PATH ~/.chainreaction/font.ttf --SAVED_GAME_PATH ~/.chainreaction/ \$*" >> /usr/bin/chain
		chmod +x /usr/bin/chain
	fi
fi
echo "creating .chainreaction directory in home..."
mkdir ~/.chainreaction
cp chain ~/.chainreaction/chain
cp support/font.ttf ~/.chainreaction
cp support/chain_help.txt ~/.chainreaction
echo "game successfully installed"
