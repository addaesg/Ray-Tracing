# Ray-Tracing

<div style="text-align:center">
    <image src =https://user-images.githubusercontent.com/61971951/158565382-e7eb1348-0f76-4bc3-a0c5-2f0f4d10394d.png alt="Logo Cin">
</div>


Este é o repositório para o projeto de Ray Tracing da cadeira de Programação Gráfica do Centro de Informática da UFPE. 
Foi implementado _from scracth_ usando C++.

    

 ## 1. Especificação:
   [Especificação Ray-Tracing 2021-2.pdf](https://github.com/addaesg/Ray-Tracing/files/8260225/Especificacao.Ray-Tracing.2021-2.pdf)
   

    
## 2. Estrutura
A estrutura do repositório, segue:
    
```   
    
MAIN
  |___ Implementation_uml
  |        |__ *.drawio
  |
  |___ Testes
  |        |__ Primeira Entrega
  |        |           |_ Input
  |        |           |    |_ *.txt
  |        |           |_ Ouput
  |        |                |_ *.png
  |        |                |_ *.ppm
  |        |__ Segunda Entrega
  |        |__ Terceira entrega
  |
  |___ Referencias
  |        |__ EspecificaçãoProjeto.pdf
  |        |__ *.pdf
  |
  |___ Primeira_Entrega_Stable
           |__ *.h
           |__ *.cpp
           |__ executável
           |__ output.ppm

```

    
    
    
## 3. Sobre as versões
Cada entrega tem um subdiretório na branch Main.
    
**Não atualize a pasta referente a uma entrega depois da deadline**
    
    
    
    
## 4. Sobre a fazer a build
_**Obs.:** Os comandos abaixo se referem à primeira entrega._ 
    
**Se você está usando o compilador g++, rode no diretório ```X_Entrega_Stable```:**
    
```
g++ atom.cpp mathutils.cpp shapes.cpp space.cpp media.cpp main.cpp
```
**A fim de executar:**
```
./a.out < PathDoArquivoDeInput.txt
```
_O arquivo .ppm é gerado como "Output.ppm" no diretório do main.cpp_
     
                                                     
### 4.1 Instalar dependencias
                                  
                                  
#### 4.1.1 Install g++ Compiler
                                  
 _For linux user, **run**:_
                                  
```sudo apt install build-essential```
_or_
```sudo apt install g++```                                     
