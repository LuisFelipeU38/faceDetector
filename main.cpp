#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <omp.h> 

using namespace std;
using namespace cv;

// Función para detectar y guardar los rostros detectados
void detectFacesAndSaveCrops(const Mat& image, CascadeClassifier& face_cascade, vector<Rect>& faces)
{
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);  
    equalizeHist(gray_image, gray_image);         

    GaussianBlur(gray_image, gray_image, Size(5, 5), 1.5);
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30), Size());

    #pragma omp parallel for
    for (size_t i = 0; i < faces.size(); i++)
    {
        Mat faceROI = image(faces[i]);  
        string face_filename = "rostro_" + to_string(i) + ".jpg";
        imwrite(face_filename, faceROI);  
    }
}

// Función para marcar los rostros detectados y guardar la imagen final
void markFacesAndSaveImage(const Mat& image, const vector<Rect>& faces, const string& output_image_name)
{
    Mat colored_image;
    applyColorMap(image, colored_image, COLORMAP_OCEAN);  

    // Dibujar rectángulos alrededor de cada rostro detectado
    for (size_t i = 0; i < faces.size(); i++)
    {
        rectangle(colored_image, faces[i], Scalar(0, 255, 0), 2);
    }

    // Guardar la imagen con los rostros marcados
    imwrite(output_image_name, colored_image);
    cout << "Imagen con rostros guardada como " << output_image_name << endl;

    Mat resized_image;
    Size new_size(800, 600); 
    resize(colored_image, resized_image, new_size);
    namedWindow("Rostros detectados", WINDOW_NORMAL);
    imshow("Rostros detectados", resized_image);
    waitKey(0);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Uso: " << argv[0] << " <imagen.jpeg>" << endl;
        return -1;
    }

    string image_path = argv[1];
    Mat image = imread(image_path, IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Error al cargar la imagen!" << endl;
        return -1;
    }

    CascadeClassifier face_cascade;
    if (!face_cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt2.xml"))
    {
        cout << "Error al cargar el archivo haarcascade_frontalface_alt2.xml" << endl;
        return -1;
    }

    // Vector para almacenar los rostros detectados
    vector<Rect> faces;

    // Detectar rostros y guardar los recortes de rostros
    detectFacesAndSaveCrops(image, face_cascade, faces);

    // Marcar los rostros en la imagen original y guardar la imagen marcada
    markFacesAndSaveImage(image, faces, "rostros_marcados.jpg");

    return 0;
}