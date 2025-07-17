A minha proposta é um site onde os usuários podem deixar reviews pessoais, um diário de reviews, de certa maneira.
Tive a idéia de fazer isso quando fui pedir um ifood, e acidentalmente pedi em um restaurante que já tinha pedido antes e tinha tido uma mau experiencia (Que se repetiu)

O projeto só possui uma database, composta por 6 rows [`id`, `username`, `email`, `password`, `user-data` e `remember_token`]
O site possui a possiblidade de login persistente através do salvamento de uma chave nos cookies do navegador.
Ao acessar o menu principal, o usuário tem a possibilidade de 

* Fazer logout (que também limpará seu cookie de login)
* Acessar sua página de perfil
* Começar a criar suas reviews

Acessando a sua página de perfil, o usuário poderá alterar sua senha de acesso ou apelido/username.
Sem a possibilidade de alterar o e-mail, sendo própriamente refletido nos dados armazenados.

No menu principal, o usuário pode clicar no botão azul no canto inferior direito para abrir um menu modal, onde ele pode inserir as informações pertinentes à sua crítica.
O sistema vai então armazenar o input do usuário em na row `user-data`(Um `JsonArray`) no banco de dados e armazenar a imagem (Se inclusa) no diretório `root/Uploads`.
A página será então atualizada para mostrar a lista atualizada de críticas.
Usuário poderá então, se quiser, editar livremente suas críticas antigas clicando no botão que aparece no card quando passar o mouse em cima, para caso um restaurante ruim fique bom, ou vice-versa, por exemplo.

- Todas as páginas verificam o seu estado de login, redirecionando o usuário para a página pertinente caso esteja tentando acessar algo que não deve.(Por exemplo, tentar acessar o perfil sem estar logado)
- Todos os inputs de usuário são sanitizados afims de segurança.
- Tirando as telas de login, utilizei `Bootstrap` pesadamente para a estilização do site (Também utilizei `Font Awesome` para as estrelas)