FROM ubuntu:latest

RUN apt update && apt upgrade -y

RUN apt install curl -y

RUN apt install nano -y

RUN apt install wget -y

RUN apt install zsh -y

RUN apt install git -y
RUN git config --global user.name "vsivanat" && \
	git config --global user.email "vsivanat@student.42.fr"

RUN apt install build-essential -y 

RUN zsh -c "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)" | true

COPY .zsh_aliase /root/.zsh_aliase

RUN wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh && \
	chmod 755 install.sh && \
	./install.sh && \
	rm install.sh

RUN chsh -s zsh

RUN cat ~/.zsh_aliase >> ~/.zshrc

CMD ["zsh"]
