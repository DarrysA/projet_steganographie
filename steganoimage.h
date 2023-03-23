#ifndef STEGANOIMAGE_H
#define STEGANOIMAGE_H

#include <QMainWindow>
#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

namespace Ui {
class Steganoimage;
}

class Steganoimage : public QMainWindow //la classe steganoimage est héritée de la classe QMainWindow pour créer une fenêtre
{
    Q_OBJECT

public:
    explicit Steganoimage(QWidget *parent = 0);
    ~Steganoimage(); //cette fonction est le destructeur

private slots:

    void on_bouton_ajout_couleur_clicked(); //cette fonction permet d'ajouter une image couleur et de l'afficher sur l'interface
    void on_bouton_ajout_NB1_clicked(); //cette fonction ajoute la première image noir et blanc et l'affiche
    void on_bouton_ajout_NB1_2_clicked(); //cette fonction ajoute la deuxième image noir et blanc et l'affiche
    void on_bouton_ajout_NB1_3_clicked(); //cette fonction ajoute la troisième image noir et blanc et l'affiche

    void on_bouton_occultation_clicked(); //cette fonction occulte les trois images en noir et blanc dans l'image couleur lorsqu'on appuie sur le bouton correspondant sur l'interface
    void on_bouton_extraction_clicked(); //cette fonction extrait les images noir et blanc de l'image couleur lorsqu'on appuie sur le bouton correspondant

    void on_bouton_sauvegarde_clicked(); //cette fonction permet de sauvegarder en cliquant sur le bouton
    

    void on_bouton_ouvrir_clicked(); //cette fonction permet d'ouvrir une image dont il faut extraire les images en noir et blanc et de l'afficher

private:
    Ui::Steganoimage *ui;
    
    Mat m_image; //cette variable sert à accueillir l'image couleur puis l'image transformée

    Mat m_image1; //cette variable sert à accueillir l'image en noir et blanc qui ira dans les bits de la couleur bleue (image 1)
    Mat m_image2; //cette variable sert à accueillir l'image en noir et blanc qui ira dans les bits de la couleur verte (image 2)
    Mat m_image3; //cette variable sert à accueillir l'image en noir et blanc qui ira dans les bits de la couleur rouge (image 3)

    Mat m_img_ex1; //cette variable sert à accueillir l'image 1 une fois extraite
    Mat m_img_ex2; //cette variable sert à accueillir l'image 2 une fois extraite
    Mat m_img_ex3; //cette variable sert à accueillir l'image 3 une fois extraite

    string m_path; //cette variable sert à contenir le chemin de l'image originale en couleur, puis le chemin de sauvegarde de cette image
    string m_path1; //cette variable sert à contenir le chemin de l'image 1 pour son ouverture
    string m_path2; //cette variable sert à contenir le chemin de l'image 2 pour son ouverture
    string m_path3; //cette variable sert à contenir le chemin de l'image 3 pour son ouverture

    //Steganoimage();
    Steganoimage(Mat image, string path); //il s'agit du constructeur avec variables qui permet d'initialiser les variables
    Steganoimage(const Steganoimage& S);//il s'agit du constructeur copie

    Mat AjoutImageCouleur(string path); //cette fonction permet d'ajouter une image couleur dans le programme
    Mat AjoutImageNB1(string path);//ces 3 fonctions permetttent d'ajouter des images en noir et blanc dans le programme
    Mat AjoutImageNB2(string path);
    Mat AjoutImageNB3(string path);

    Mat Occultation(); //cette fonction permet d'occulter les images en noir et blanc dans l'image couleur et renvoie la nouvelle image créée
    QImage convertOpenCVMatToQtQImage(Mat mat); //cette fonction convertit les images de type Mat en images de type QImage, ce qui est nécessaire pour l'affichage

    Mat Extraction_Image_bleu(); //cette fonction extrait l'image noir et blanc cachée dans les bits de la couleur bleue et la retourne
    Mat Extraction_Image_vert(); //cette fonction extrait l'image noir et blanc cachée dans les bits de la couleur verte et la retourne
    Mat Extraction_Image_rouge(); //cette fonction extrait l'image noir et blanc cachée dans les bits de la couleur rouge et la retourne

    void Sauvegarde();//Cette fonction a pour but de sauvegarder l'image après occultation au format png
    



};

#endif // STEGANOIMAGE_H
