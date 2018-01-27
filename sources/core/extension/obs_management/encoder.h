/*
    Encoders are specific implementations of video/audio encoders,
    which are used with outputs that use encoders.
    x264, NVENC, Quicksync are examples of encoder implementations.
*/

namespace wot_stream::extension::obs_management {

    class Encoder {
    public:
        Encoder();
        ~Encoder();

    private:

    };

    Encoder::Encoder() {}

    Encoder::~Encoder() {}
}