# AEP 2024

## Diagrama de Caso de Uso 
![Diagrama de Caso de Uso](https://i.imgur.com/JkaSdz1.png)


## Sobre o projeto
Este projeto consiste em um mini menu que permite a inserção e remoção de usuários e senhas, com as seguintes verificações de segurança para a senha:

- 8 a 12 caracteres;
- Deve ter letra maiúscula;
- Deve ter letra minúscula;
- Deve ter caracteres especiais;
- Deve ter número.

Após a validação, a senha é criptografada salva no arquivo `usuarios.txt`. O menu também permite remover um usuário apenas digitando o nome de usuário e exibe a lista dos cadastrados no arquivo de texto.

## Como funciona a CRIPTOGRAFIA?
- Primeiro tanto usuario quanto senha são invertidos (`filipe viraria epilif`);
- Após isso, uma função que verifica vogais é acionada e ela troca a vogal incrementando o valor 2;
- Após isso ele é adicionado a um laço de repetição que faz o incremento de 5 caracteres seguindo a tabela `ASCII`.


Adicionalmente, foi implementado um menu para exibir informações sobre o projeto, inspirado pela brilhante ideia do professor Alexandre Moreno. Nesse menu, incluímos os integrantes do grupo e as bibliotecas utilizadas.

## Mensagem Final

Esse projeto foi um desafio difícil, pois me fez sair da minha zona de conforto e pensar criticamente. Muitas das soluções não foram abordadas em aula, o que exigiu pesquisa e iniciativa. No geral, consegui aplicar um design que achei bonito e fiz um bom trabalho. Agradeço mais uma vez ao professor Alexandre Moreno e ao João Ferlini, que nos orientaram durante o processo!


## Foi utilizada a Linguagem C no Projeto!
[![Linguagens utilizadas](https://i.imgur.com/zd6KOy3.png)](https://youtu.be/7812yUSJsu8)


##       Acesse o vídeo da amostra do projeto, basta clicar na imagem!
[![Video](https://i.imgur.com/kj5Y1YK.png)](https://youtu.be/HyYJ4wrdal0)

https://github.com/filiperuizb/AEP-2024
