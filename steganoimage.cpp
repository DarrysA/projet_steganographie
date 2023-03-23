#include "steganoimage.h"
#include "ui_steganoimage.h"
#include <QFileDialog>
#include <QMessageBox>
using namespace cv;
using namespace std;

Steganoimage::Steganoimage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steganoimage)
{
    ui->setupUi(this);
}

Steganoimage::~Steganoimage() //il s'agit du destructeur. Les images de type Mat sont gérées automatiquement par OpenCV, il y a juste besoin de gérer les chemins d'accès
{
    m_path = " ";
    m_path1 = " ";
    m_path2 = " ";
    m_path3 = " ";

    delete ui;
}



Steganoimage::Steganoimage(Mat image, string path) //ce constructeur paramétrique sert à créer un nouvel objet de type Steganoimage à l'aide d'une image et d'un chemin
{
    m_image = image;
    m_path = path;
}



Steganoimage::Steganoimage(const Steganoimage& S) //ce constructeur par recopie permet de créer un nouvel objet de type Steganoimage
{
    m_image = S.m_image;
    m_image1 = S.m_image1;
    m_image2 = S.m_image2;
    m_image3 = S.m_image3;

    m_img_ex1 = S.m_img_ex1;
    m_img_ex2 = S.m_img_ex2;
    m_img_ex3 = S.m_img_ex3;

    m_path = S.m_path;
    m_path1 = S.m_path1;
    m_path2 = S.m_path2;
    m_path3 = S.m_path3;

}



Mat Steganoimage::AjoutImageCouleur(string path)
{
    m_path = path;
    m_image = imread(m_path, IMREAD_COLOR); //on lit le fichier image en tant qu'image en couleur contenu dans l'emplacement de m_path

    //dans le but de dénicher plus facilement les erreurs, on crée une boucle qui vérifie si l'image a bien été ouverte
    if (m_image.empty())
    {
        cout << endl << "Erreur : l'image en couleur n'a pas pu être ajoutee" << endl;
        cout << "Chemin de l'image : " << m_path << endl;
        return m_image;
    }
    else
    {
        cout << "Ajout de l'image couleur reussi. Le chemin de l'image est : " << m_path << endl;
        return m_image;
    }
}



Mat Steganoimage::AjoutImageNB1(string path) //cette fonction permet d'ajouter l'image 1 en noir et blanc et est très similaire à la fonctio AjoutImageCouleur
{
    m_path1 = path;
    m_image1 = imread(m_path1, IMREAD_GRAYSCALE); //on lit le fichier image en tant qu'image en noir et blanc grâce à l'argument IMREAD_GRAYSCALE
    if (m_image1.empty()) //la boucle if
    {
        cout << endl << "Erreur : l'image en noir et blanc n'a pas pu être trouvee" << endl;
        cout << "Chemin de l'image : " << m_path1 << endl;
        return m_image1;
    }
    else
    {
        cout << "Ajout de la premiere image en noir et blanc reussi. Le chemin de l'image est : " << m_path1 << endl;
        return m_image1;
    }
}



Mat Steganoimage::AjoutImageNB2(string path) //cette fonction permet d'ajouter l'image 2 en noir et blanc
{
    m_path2 = path;
    m_image2 = imread(m_path2, IMREAD_GRAYSCALE);
    if (m_image2.empty())
    {
        cout << endl << "Erreur : l'image en noir et blanc n'a pas pu être trouvee" << endl;
        cout << "Chemin de l'image : " << m_path2 << endl;
        return m_image2;
    }
    else
    {
        cout << "Ajout de la 2e image en noir et blanc reussi. Le chemin de l'image est : " << m_path2 << endl;
        return m_image2;
    }
}



Mat Steganoimage::AjoutImageNB3(string path) //cette fonction permet d'ajouter l'image 3 en noir et blanc
{
    m_path3 = path;
    m_image3 = imread(m_path3, IMREAD_GRAYSCALE);;
    if (m_image3.empty())
    {
        cout << "Erreur : l'image en noir et blanc n'a pas pu être trouvee" << endl;
        cout << "Chemin de l'image : " << m_path3 << endl;
        return m_image3;
    }
    else
    {
        cout << "Ajout de la troisieme image en noir et blanc reussi. Le chemin de l'image est : " << m_path3 << endl;
        return m_image3;
    }
}



Mat Steganoimage::Occultation() //cette fonction a pour but d'occulter les images en noir et blanc dans l'image en couleur
{

    //on masque d'abord les 4 bits inférieurs des pixels de chaque image grâce à l'opérateur AND.
    //En effet, il se produit une multiplication bit à bit telle que : 1111 1111 & 0xf0 = 1111 1111 & 1111 0000 = 1111 0000
    //Cela est valable pour n'importe quel nombre en binaire.

    for (int i = 0; i < m_image.rows; i++) //cette boucle for permet de remplacer, sur toute l'image, la valeur de chaque couleur par une valeur dont les bits de poids faible sont à 0
    {
        for (int j = 0; j < m_image.cols; j++)
        {
            for (int k = 0; k < 3; k++) //la variable k représente la couleur : 0 pour le bleu, 1 pour le vert et 2 pour le rouge
            {
                m_image.at<Vec3b>(i, j)[k] = m_image.at<Vec3b>(i, j)[k] & 0xf0;
                //on met à 0 chaque valeur de chaque couleur
            }
        }
    }

    cout << endl << "Mise a 0 des bits de poids faible de la premiere image" << endl;
    for (int i = 0; i < m_image1.rows; i++) //cette boucle for permet de mettre à 0 les bits de poids faible de la première image en noir et blanc.
    {
        for (int j = 0; j < m_image1.cols; j++)
        {
            //il n'y a besoin que de 2 boucles for car les images en noir et blanc ne possèdent qu'un canal
            m_image1.at<uchar>(i, j) = m_image1.at<uchar>(i, j) & 0xf0; //on met à 0 les bits de poids faible de l'intensité de l'image 1 en noir et blanc
        }
    }

    cout << "Mise a 0 des bits de poids faible de la deuxieme image" << endl;
    for (int i = 0; i < m_image2.rows; i++)
    {
        for (int j = 0; j < m_image2.cols; j++)
        {
            m_image2.at<uchar>(i, j) = m_image2.at<uchar>(i, j) & 0xf0;
        }
    }

    cout << "Mise a 0 des bits de poids faible de la troisieme image" << endl;
    for (int i = 0; i < m_image3.rows; i++)
    {
        for (int j = 0; j < m_image3.cols; j++)
        {
            m_image3.at<uchar>(i, j) = m_image3.at<uchar>(i, j) & 0xf0;
        }
    }


    cout << "Decalage des bits de la premiere image" << endl;
    //ensuite, on décale les bits de chaque image en noir et blanc des bits supérieurs vers les bits inférieurs :
    for (int i = 0; i < m_image1.rows; i++)
    {
        for (int j = 0; j < m_image1.cols; j++)
        {
            // l'opérateur >> permet de décaler les bits vers la droite, on les décale donc de 4 bits.
            m_image1.at<uchar>(i, j) = m_image1.at<uchar>(i, j) >> 4;
        }
    }

    cout << "Decalage des bits de la 2e image" << endl;
    for (int i = 0; i < m_image2.rows; i++)
    {
        for (int j = 0; j < m_image2.cols; j++)
        {
            m_image2.at<uchar>(i, j) = m_image2.at<uchar>(i, j) >> 4;
        }
    }

    cout << "Decalage des bits de la 3e image" << endl;
    for (int i = 0; i < m_image3.rows; i++)
    {
        for (int j = 0; j < m_image3.cols; j++)
        {
            m_image3.at<uchar>(i, j) = m_image3.at<uchar>(i, j) >> 4;

        }
    }

    //il ne reste plus qu'à additionner les bits de chaque image avec les différentes couleurs de l'image de base
    //on place les bits de l'image en noir et blanc dans les bits inférieurs du channel 0 de l'image couleur (couleur bleue) :
    cout << "Addition de la premiere image dans le bleu" << endl;
    for (int i = 0; i < m_image1.rows; i++)
    {
        for (int j = 0; j < m_image1.cols; j++)
        {
            m_image.at<Vec3b>(i, j)[0] = m_image.at<Vec3b>(i, j)[0] | m_image1.at<uchar>(i, j); //l'opérateur OR permet "d'additionner" les valeurs des deux images
        }
    }

    //on place les bits de l'image en noir et blanc dans les bits inférieurs du channel 1 de l'image couleur (couleur verte) :
    cout << "Addition de la 2e image dans le vert" << endl;
    for (int i = 0; i < m_image2.rows; i++)
    {
        for (int j = 0; j < m_image2.cols; j++)
        {
            m_image.at<Vec3b>(i, j)[1] = m_image.at<Vec3b>(i, j)[1] | m_image2.at<uchar>(i, j);
        }
    }

    //on place les bits de l'image en noir et blanc dans les bits inférieurs du channel 2 de l'image couleur (couleur rouge) :
    cout << "Addition de la 3e image dans le rouge" << endl;
    for (int i = 0; i < m_image3.rows; i++)
    {
        for (int j = 0; j < m_image3.cols; j++)
        {
            m_image.at<Vec3b>(i, j)[2] = m_image.at<Vec3b>(i, j)[2] | m_image3.at<uchar>(i, j);
        }
    }

    return m_image;
}



Mat Steganoimage::Extraction_Image_bleu()
{
    //on crée une image en noir et blanc qui va être remplacée par celle qui va être extraite
    Mat image_extraite(m_image.rows, m_image.cols, CV_8UC1, Scalar(70));

    cout << endl << "Extraction de la premiere image" << endl;
    cout << "Extraction des bits inferieurs..." << endl;

    for(int i = 0; i < m_image.rows; i++) //cette boucle for permet de sélectionner tous les pixels de l'image en passant par toutes les coordonnées possibles
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            //on met à 0 les bits de poids fort de l'image couleur post-occultation, et on écrit ces données dans l'image extraite
            image_extraite.at<uchar>(i,j) = m_image.at<Vec3b>(i,j)[0] & 0x0f;
        }
    }

    cout << "Deplacement des bits inferieurs vers les bits superieurs..." << endl;
    for(int i = 0; i < m_image.rows; i++)
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            //ensuite, on déplace les bits de poids faible de 4 rangs vers la gauche afin qu'ils deviennent des bits de poids fort
            image_extraite.at<uchar>(i,j) = image_extraite.at<uchar>(i,j) << 4;
        }
    }

    return image_extraite;
}



Mat Steganoimage::Extraction_Image_vert() //cette fonction permet d'extraire l'image en noir et blanc contenue dans le channel 1 de l'image couleur
{
    Mat image_extraite(m_image.rows,m_image.cols, CV_8UC1, Scalar(70));

    cout << endl << "Extraction de la deuxieme image" << endl;
    cout << "Extraction des bits inferieurs..." << endl;

    for(int i = 0; i < m_image.rows; i++)
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            image_extraite.at<uchar>(i,j) = m_image.at<Vec3b>(i,j)[1] & 0x0f;
        }
    }

    cout << "Deplacement des bits inferieurs vers les bits superieurs..." << endl;
    for(int i = 0; i < m_image.rows; i++)
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            image_extraite.at<uchar>(i,j) = image_extraite.at<uchar>(i,j) << 4;
        }
    }
    cout << "Fin de l'extraction de la deuxieme image" << endl;

    return image_extraite;
}



Mat Steganoimage::Extraction_Image_rouge() //cette fonction permet d'extraire l'image en noir et blanc contenue dans le channel 2 de l'image couleur
{
    Mat image_extraite(m_image.rows, m_image.cols, CV_8UC1, Scalar(70));

    cout << endl << "Extraction de la troisieme image" << endl;
    cout << "Extraction des bits inferieurs..." << endl;

    for(int i = 0; i < m_image.rows; i++)
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            image_extraite.at<uchar>(i,j) = m_image.at<Vec3b>(i,j)[2] & 0x0f;
        }
    }

    cout << "Deplacement des bits inferieurs vers les bits superieurs..." << endl;
    for(int i = 0; i < m_image.rows; i++)
    {
        for(int j = 0; j < m_image.cols; j++)
        {
            image_extraite.at<uchar>(i,j) = image_extraite.at<uchar>(i,j) << 4;
        }
    }
    cout << "Fin de l'extraction de la troisieme image" << endl;

    return image_extraite;
}



void Steganoimage::Sauvegarde() //cette fonction permet de sauvegarder une image couleur
{
    cout << endl << "Sauvegarde de l'image..." << endl;

    QString path; //on déclare une variable de type QString car la fonction getSaveFileName ne retourne qu'une variable de type QString

    //d'abord, on demande à l'utilisateur de choisir le chemin de destination de l'image
    path = QFileDialog::getSaveFileName(this, tr("Sauvegarder l'image occultee"), "C:/Users", tr("Image Files (*.png *.bmp)"));
    m_path = path.toStdString(); //on convertit ensuite le chemin fourni par l'utilisateur

    vector<int> compression_params; //on établit les paramètres de compression de l'image
    compression_params.push_back(IMWRITE_PNG_COMPRESSION); //on fait en sorte que l'image soit sauvegardée au format PNG, sinon il y a trop de pertes d'informations

    bool isSuccess = imwrite(m_path, m_image, compression_params); //on enregistre l'image grâce à la fonction imwrite
    if (isSuccess == false) //on teste ensuite si la sauvegarde s'est passée correctement
    {
     cout << "Erreur : l'image n'a pas pu etre sauvegardee" << endl;
    }
}



//Procédure de conversion du format Mat de OpenCV vers le format QImage de Qt.
//Ce format permet d'afficher simpelement des images dans les labels de l'interface graphique
QImage Steganoimage::convertOpenCVMatToQtQImage(Mat mat)
{
    if(mat.channels() == 1) //une première boucle if vérifie si l'image est une image noir et blanc
    {
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        //si l'image est une image en noir et blanc, la fonction retourne une image au format "Format_Indexed8" qui correspond à une image en noir et blanc
    }
    else
    if(mat.channels() == 3) //si l'image n'est pas une image en noir et blanc, on teste si c'est une image couleur
    {
        cvtColor(mat, mat, CV_BGR2RGB); //si c'est une image couleur, on la convertit au format RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        //on déplace ensuite les données de l'image de type Mat vers l'image de type QImage
    }
    return QImage(); //si l'image ne correspond à aucun des deux types, on retourne une image QImage vide
}



//cette fonction permet d'ajouter une image couleur dans laquelle on va insérer les images en noir et blanc
void Steganoimage::on_bouton_ajout_couleur_clicked()
{
    //on choisit d'abord l'image à ouvrir
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir l'image couleur"), "C:/Users", tr("Image Files (*.png *.jpg *.bmp)"));
    m_path = path.toStdString(); //on convertit la variable de type QString en variable de type string pour être utilisé par la fonction AjoutImage couleur

    m_image = AjoutImageCouleur(m_path); //on ajoute ensuite l'image dans le programme
    QImage img0 = convertOpenCVMatToQtQImage(m_image); //on convertit l'image ajoutée de type Mat en image de type QImage afin de l'afficher


    //on affiche ensuite l'image sur l'interface graphique dans le label correspondant
    ui->label_image_originale->setPixmap(QPixmap::fromImage(img0).scaled(ui->label_image_originale->width(), ui->label_image_originale->height(), Qt::KeepAspectRatio));
}



void Steganoimage::on_bouton_ajout_NB1_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir l'image couleur"), "C:/Users", tr("Image Files (*.png *.jpg *.bmp)"));
    m_path1 = path.toStdString();
    m_image1 = AjoutImageNB1(m_path1);

    //on a ici une boucle conditionnelle qui permet de vérifier si l'image en noir et blanc à insérer est plus grande que l'image couleur
    if(m_image1.rows > m_image.rows && m_image1.cols > m_image.cols)
    {
        QMessageBox message;
        message.setText("Erreur : Veuillez choisir une image à occulter de même taille que l'image couleur !");
        message.exec();
    }
    else
    {
        QImage img1 = convertOpenCVMatToQtQImage(m_image1);
        ui->label_img1->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_img1->width(), ui->label_img1->height(), Qt::KeepAspectRatio));
    }

}



void Steganoimage::on_bouton_ajout_NB1_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir l'image couleur"), "C:/Users", tr("Image Files (*.png *.jpg *.bmp)"));
    m_path2 = path.toStdString();
    m_image2 = AjoutImageNB2(m_path2);


    if(m_image2.rows > m_image.rows && m_image2.cols > m_image.cols)
    {
        QMessageBox message;
        message.setText("Erreur : Veuillez choisir une image à occulter de même taille ou plus petite que l'image couleur !");
        message.exec();
    }
    else
    {
        QImage img2 = convertOpenCVMatToQtQImage(m_image2);
        ui->label_img2->setPixmap(QPixmap::fromImage(img2).scaled(ui->label_img2->width(), ui->label_img2->height(), Qt::KeepAspectRatio));
    }
}



void Steganoimage::on_bouton_ajout_NB1_3_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir l'image couleur"), "C:/Users", tr("Image Files (*.png *.jpg *.bmp)"));
    m_path3 = path.toStdString();
    m_image3 = AjoutImageNB3(m_path3);

    if(m_image3.rows > m_image.rows && m_image3.cols > m_image.cols)
    {
        QMessageBox message;
        message.setText("Erreur : Veuillez choisir une image à occulter de même taille ou plus petite que l'image couleur");
        message.exec();
    }
    else
    {
        QImage img3 = convertOpenCVMatToQtQImage(m_image3);

        ui->label_img3->setPixmap(QPixmap::fromImage(img3).scaled(ui->label_img3->width(), ui->label_img3->height(), Qt::KeepAspectRatio));
    }
}



void Steganoimage::on_bouton_occultation_clicked() //ce bouton sert à occulter les images en noir et blanc et à afficher l'image couleur après occultation
{
    if(m_image.empty()) //on vérifie d'abord si une image a été ajoutée dans m_image. Sinon, on ne peut pas procéder à l'occultation
    {
        QMessageBox message; //s'il n'y a pas d'image dans la variable m_image, on affiche une boîte de dialogue pour prévenir qu'il faut en ajouter une
        message.setText("Erreur : Veuillez choisir une image couleur afin de dissimuler 3 images en noir et blanc dedans");
    }
    else
    {//si une image a été ajoutée dans m_image précédemment, on procède à l'occultation
        Mat img_finale = Occultation();
        QImage image_finale = convertOpenCVMatToQtQImage(img_finale); //on convertit l'image pour ensuite l'afficher sur l'interface graphique
        ui->label_image_finale->setPixmap(QPixmap::fromImage(image_finale).scaled(ui->label_image_finale->width(), ui->label_image_finale->height(), Qt::KeepAspectRatio));
    }
}



void Steganoimage::on_bouton_extraction_clicked() //ce bouton sert à extraire les images en noir et blanc de l'image couleur
{
    if(ui->label_image_finale->pixmap() == 0) //on vérifie d'abord qu'une image est bien présente dans le label de l'image après occultation
    {
        QMessageBox message; //s'il n'y a pas d'image, on ne peut pas procéder à l'extraction. Un fenêtre va alors s'afficher pour prévenir l'utilisateur
        message.setText("Erreur : Veuillez occulter l'image ou charger une image avant d'en extraire les images cachees");
    }
    else
    {
        m_img_ex1 = Extraction_Image_bleu(); //on extrait chaque image de son canal correspondant
        m_img_ex2 = Extraction_Image_vert();
        m_img_ex3 = Extraction_Image_rouge();

        QImage image1 = convertOpenCVMatToQtQImage(m_img_ex1); //on convertit les images de type Mat en images de type QImage afin de les afficher
        QImage image2 = convertOpenCVMatToQtQImage(m_img_ex2);
        QImage image3 = convertOpenCVMatToQtQImage(m_img_ex3);

        //on affiche ensuite chaque image dans le label qui lui correspond sur l'interface graphique
        ui->label_img4->setPixmap(QPixmap::fromImage(image1).scaled(ui->label_img4->width(), ui->label_img4->height(), Qt::KeepAspectRatio));
        ui->label_img5->setPixmap(QPixmap::fromImage(image2).scaled(ui->label_img5->width(), ui->label_img5->height(), Qt::KeepAspectRatio));
        ui->label_img6->setPixmap(QPixmap::fromImage(image3).scaled(ui->label_img6->width(), ui->label_img6->height(), Qt::KeepAspectRatio));
    }
}

void Steganoimage::on_bouton_sauvegarde_clicked() //ce bouton sert à sauvegarder une image couleur post-occultation
{
    if(ui->label_image_finale->pixmap() == 0) //on vérifie d'abord si l'image post-occultation existe
    {
        QMessageBox message; //si cette image n'existe pas, un message s'affiche pour prévenir l'utilisateur
        message.setText("Erreur : Veuillez occulter l'image ou charger une image avant de la sauvegarder");
    }
    else
    {
        Sauvegarde(); //si l'image est affichée, on la sauvegarde
    }
}



void Steganoimage::on_bouton_ouvrir_clicked() //ce bouton sert à ouvrir une image couleur post-occultation dans le but d'en extraire les images
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir l'image couleur"), "C:/Users", tr("Image Files (*.png *.jpg *.bmp)"));
    m_path = path.toStdString();
    m_image = AjoutImageCouleur(m_path);
    QImage img0 = convertOpenCVMatToQtQImage(m_image);

    //l'image est affichée à l'emplacement de l'image post-occultation afin de la distinguer d'une image couleur originale
    ui->label_image_finale->setPixmap(QPixmap::fromImage(img0).scaled(ui->label_image_finale->width(), ui->label_image_finale->height(), Qt::KeepAspectRatio));
}
