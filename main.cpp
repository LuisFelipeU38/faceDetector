#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <omp.h> 

using namespace std;
using namespace cv;

void detectAndSaveFaces(const Mat& image, CascadeClassifier& face_cascade, const string& output_image_name);

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

    // Detectar y guardar los rostros
    detectAndSaveFaces(image, face_cascade, "rostros_marcados.jpg");

    return 0;
}

void detectAndSaveFaces(const Mat& image, CascadeClassifier& face_cascade, const string& output_image_name)
{
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);  // Convertir a escala de grises
    equalizeHist(gray_image, gray_image);         

    GaussianBlur(gray_image, gray_image, Size(5, 5), 1.5);
    vector<Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30), Size());

    Mat colored_image;
    applyColorMap(image, colored_image, COLORMAP_OCEAN);  

    // Paralelizar el bucle de marcado de rostros con OpenMP
    #pragma omp parallel for
    for (size_t i = 0; i < faces.size(); i++)
    {
        rectangle(colored_image, faces[i], Scalar(0, 255, 0), 2);
        Mat faceROI = image(faces[i]);
        string face_filename = "rostro_" + to_string(i) + ".jpg";
        imwrite(face_filename, faceROI);
    }

    imwrite(output_image_name, colored_image);
    cout << "Imagen con rostros guardada como " << output_image_name << endl;
    namedWindow("Rostros detectados", WINDOW_AUTOSIZE);
    imshow("Rostros detectados", colored_image);
    waitKey(0);
}
