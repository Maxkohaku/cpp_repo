######################
Oh My Zsh + git
######################
sudo apt install zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
vim ~/.zshrc
plugins=(git)
source ~/.zshrc

######################
zsh-autosuggestions
######################
git clone https://github.com/zsh-users/zsh-autosuggestions ~/.oh-my-zsh/custom/plugins/zsh-autosuggestions
vim ~/.zshrc
plugins=(git zsh-autosuggestions)
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ~/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting
plugins=(git zsh-syntax-highlighting)
source ~/.zshrc
