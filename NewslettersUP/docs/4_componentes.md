# Especificação de Componentes

O projeto em mãos pode ser divido em duas componentes maiores. Estas, por sua vez, poderão ser subdivididas em subcomponentes mais detalhadas.

Por duas componentes principais entendam-se:

- `frontend` - como sendo a componente que relaciona tudo o que esteja ligado a experiência do utilizador, interface da plataforma, fluxo de utilização e acessibilidade.

- `backend` - como sendo a componente que relaciona tudo o que esteja ligado com a base de dados, com a ligação às _live previews_ do conteúdo, a criação das coleções de documentos para a construção do arquivo (caso o conteúdo deixe de estar acessível _online_) e respetiva pipeline de processamento e recuperação de informação, e no geral tudo o que tenha a ver com o bastidor da plataforma (como pesquisa e filtragem de resultados, por exemplo).

## `frontend`

Como já referido anteriormente, esta componente relaciona-se com a parte mais visual do projeto.

Também dito, foi que esta componente pode ser subdividida. Por exemplo, podemos dentro desta parte explorar o seguinte:

- `timeline` - como sendo a componente visual, do frontend, responsável pela contextualização temporal do conteúdo mostrado. Esta terá vários níveis de interação (podendo aumentar ou diminuir o nível de detalhe temporal a que o período exposto de refere). É à volta desta componente que o `frontend` gira.

- `restante` - vendo o _site_ como algo de uma página só, a `timeline` é de facto a componente principal. O restante refere-se a todas as outras componentes, que mesmo não sendo as mais relevantes, importam no resultado final por questões de harmonia de todas as partes e de simbiose no seu funcionamento lógico. Destacamos, por exemplo, a barra de pesquisa, as cores utilizadas, as _thumbnails_ que dão uma amostra de um certo conteúdo e os filtros que se possam aplicar.

## `backend`

Como já referido anteriormente, esta componente relaciona-se com a parte mais abstrata e lógica do projeto. As componentes desta parte, funcionam como que as engrenagens da plataforma, para que o visual do `frontend` tenha também um lado funcional.

Também dito, foi que esta componente pode ser subdividida. Por exemplo, podemos dentro desta parte explorar o seguinte:

- `base de dados` - 

- `API` - 

- `pipeline` - ... para processamento e indexação da informação