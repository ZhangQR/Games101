#include "Triangle.hpp"
#include "rasterizer.hpp"
#include "../include/Eigen"
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
constexpr double MY_ANG_TO_RAD = 3.1415926/180;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float rotation_rad_angle = rotation_angle * MY_ANG_TO_RAD;
    model <<    std::cos(rotation_rad_angle),   -std::sin(rotation_rad_angle),  0,0,
                std::sin(rotation_rad_angle),   std::cos(rotation_rad_angle),   0,0,
                0,                              0,                              1,0,
                0,                              0,                              0,1;

    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function
    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
    float tan_theta = std::tan(eye_fov * 0.5 * MY_ANG_TO_RAD);
    Eigen::Matrix4f perpective_tranform;
    perpective_tranform <<  
    -1/(aspect_ratio*tan_theta) ,0              ,0                          ,0,
    0,                          -1/tan_theta    ,0                          ,0,
    0,                          0              ,(zNear+zFar)/(zNear-zFar)  ,2*zFar*zNear/(zFar-zNear),
    0,                          0              ,1                          ,0;
    return perpective_tranform;
}

// 绕过原点的任意轴旋转
Eigen::Matrix4f get_rotation(Vector3f axis, float angle)
{
    Eigen::Vector3f w = axis.normalized();
    Eigen::Vector3f t = w;  // 保证 t 跟 w 不能太接近，所以把最小的分量直接取 1
    auto* min_number = t(0) < t(1) ? &t(0) : &t(1);
    min_number = *min_number < t(2) ? min_number : &t(2);
    *min_number = 1;
    Eigen::Vector3f u=t.cross(w).normalized();
    Eigen::Vector3f v = w.cross(u);
    Eigen::Matrix4f P;
    P<< u(0),   v(0),   w(0),   0,
        u(1),   v(1),   w(1),   0,
        u(2),   v(2),   w(2),   0,
        0,      0,      0,      1;
    Eigen::Matrix4f R;
    float angle_ran = angle * MY_ANG_TO_RAD;
    R<< std::cos(angle_ran),    -std::sin(angle_ran),   0,  0,
        std::sin(angle_ran),    std::cos(angle_ran),    0,  0,
        0,                      0,                      1,  0,
        0,                      0,                      0,  1;
    return P * R * (P.inverse());
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        // AD 控制绕着 Z 轴旋转
        //r.set_model(get_model_matrix(angle));

        // AD 控制绕着任意轴旋转
        r.set_model(get_rotation(Eigen::Vector3f(1,1,0),angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);

        // Debug 的时候，比如要在 SetPixel 里面输出，这个可以改大一点，不然会卡死
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
