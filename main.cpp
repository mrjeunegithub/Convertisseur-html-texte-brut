#include <iostream>
#include <fstream>
#include <cstring>

char *to_text(char *html);
char*read_file(const char *filename);
int main(int argc, char **argv) {
    char* html = read_file("index.html");
    if (!html) {
        perror("Erreur");
        return 1;
    }

    char * text_brut= to_text(html) ;
    if (text_brut)  {
         std::cout << "Texte brut :\n" << text_brut << std::endl;


        std::ofstream f("texte.txt");
        if (f.is_open()) {

            f << text_brut;
            f.close() ;
            std::cout << "Texte stocké dans 'texte.txt'" << std::endl;
        } else {
            std::cout << "Erreur d'écriture du fichier" << std::endl;
        }
    }
    

    free(text_brut);
    free(html);

    return 0;
}


char *to_text(char *html)  {
    char *text = (char *) malloc(strlen(html) + 1);  // Correction : cast malloc
    if (!text) {
        perror("Erreur d'allocation mémoire ") ;
        return nullptr;   
    }

    char *src = html, *whrite = text ;   
    int inTag =0, last_space = 1, saut_ligne = 0;

    while (*src) {
        if (*src == '<') {  
            inTag = 1;

            // Vérifier les balises nécessitant un saut de ligne
            if (strncmp (src, "<br", 3) == 0 ||  strncmp(src, "<p", 2) == 0 || strncmp(src, "<h1", 2) == 0 || strncmp(src, "<h2", 3) == 0 || strncmp(src, "<h3", 3) == 0 || strncmp(src, "<h4", 3) == 0 || strncmp(src, "<h5", 3) == 0 || strncmp(src, "<h6", 3) == 0 || strncmp(src, "<title", 6) == 0 || strncmp(src, "<div", 4) == 0 || strncmp(src, "<pre", 4) == 0 || strncmp(src, "<table", 6) == 0 || strncmp(src, "<tbody", 6) == 0 || strncmp(src, "<thead", 6) == 0 || strncmp(src, "<tfoot", 6) == 0 || strncmp(src, "<img", 4) == 0 || strncmp(src, "<figure", 7) == 0 || strncmp(src, "<address", 8) == 0 || strncmp(src, "<form", 5) == 0 || strncmp(src, "<section", 8) == 0 || strncmp(src, "<article", 8) == 0 || strncmp(src, "<li", 3) == 0) {
                if (saut_ligne< 2){
                    *whrite++ = '\n' ;
                    saut_ligne++;
                }
                
                
            }

        } else if (*src == '>') {  
             inTag = 0 ;
            src++;
            continue;
        }  else if (!inTag) {  
            if (isspace(*src)) {  
                if (!last_space) {  
                    *whrite++ = ' ';
                    last_space = 1;
                    saut_ligne = 0;
                }
            } else {  
                *whrite++= *src;
                last_space =  0;
            }   
        }
         src++;
    }

    // Supprimer l'espace final inutile
    if (whrite > text && *(whrite - 1) == ' ') {
        whrite--;
         
    }

    *whrite = '\0';
    return  text;
}


 char*read_file(const char *filename)  {
    std::string lien_html;
    std::cout<< "entrer le lien vers votre fichier html"<< std::endl;
    std::cin >> lien_html ;
    
    std::ifstream file (lien_html, std::ios::ate) ;

    if(!file.is_open()){ 
        std::cout << "erreur, impossible d'ouvrir le fichier "<<lien_html << std::endl;
        return nullptr;  
    }    

     std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg) ;

    char* html_file = (char*)malloc (file_size+1) ;   
    if(!html_file ){

         std::cout << "erreur, impossible d'allouer de la mémoire." << std::endl;
        return nullptr ;  
    
    }


    file.read(html_file, file_size);
    html_file[file_size]= '\0';
    file.close() ;

    return html_file;
}
