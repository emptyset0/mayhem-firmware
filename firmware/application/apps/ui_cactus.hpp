#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_tabview.hpp"
#include "ui_navigation.hpp"
#include "string_format.hpp"
#include "transmitter_model.hpp"
#include "ui_transmitter.hpp"

namespace ui
{
    class CactusTxView : public View                                // App class declaration
    {
    public:
        CactusTxView(NavigationView &nav, Rect parent_rect);                          // App class init function declaration
        CactusTxView(const CactusTxView&) = delete;
        CactusTxView(CactusTxView&&) = delete;
        CactusTxView& operator=(const CactusTxView&) = delete;
        CactusTxView& operator=(CactusTxView&&) = delete;
        ~CactusTxView();
        void focus() override;
        //void send_msg(const std::string& message);
        long long timer_scr = 0;
        int interval = 10000;

    private:
        /*
        void update();                                            // Function declaration
        MessageHandlerRegistration message_handler_update{        // Example, not required: MessageHandlerRegistration class
            Message::ID::DisplayFrameSync,                        // relays messages to your app code from baseband. Every time you 
            [this](const Message *const) {                        // get a  DisplayFrameSync message the update() function will
                this->update();                                   // be triggered.  
            }};
        */

        //void send_msg(const std::string& message);
        //void start_tx(std::string& message);                                         // Function declarations
        //void stop_tx();
        void on_tx_progress(const uint32_t progress, const bool done); 
        void on_timer();
        void on_hide();
        void terminate_loop();

        Thread* loopthread{nullptr};

        //TransmitterView tx_view{
        //    14 * 16,
        //    50000,
        //    9};

        Labels labels{
            {{1 * 8, 4 * 8}, "Time Interval:", Theme::getInstance()->fg_light->foreground},
            {{21 * 8, 4 * 8}, "s", Theme::getInstance()->fg_light->foreground},};

        class MilliToDecField : public NumberField
        {
        public:
            MilliToDecField(Point parent_pos, int length, range_t range, int32_t step, char fill_char, bool can_loop)
            : NumberField(parent_pos, length, range, step, fill_char, can_loop){}

            void virtual paint(Painter& painter) {
                //const auto text = to_string_decimal(value()/1000.0, 1) + " ";
                const auto text = to_string_dec_int(value()/1000) + "." + to_string_dec_int((value()%1000)/100) + " ";

                const auto paint_style = has_focus() ? style().invert() : style();

                painter.draw_string(
                    screen_pos(),
                    paint_style,
                    text);
            }
        };

        MilliToDecField interval_nf{
            {16 * 8, 4 * 8},
            4,
            {5000, 20000},
            100,
            ' ',
            true};

        //Button button_1{
        //    {19, 204, 96, 24},
        //    "1"};

        //Button button_2{
        //    {125, 204, 96, 24},
        //    "2"};

        //Button button_3{
        //    {72, 164, 96, 24},
        //    "3"};

        Button button_start{
            {72, 100, 96, 48},
            "START"};
        
        const Style& style_start = *Theme::getInstance()->fg_green;
        const Style& style_stop = *Theme::getInstance()->fg_red;

        bool looping_ = false;

        void set_looping(bool looping);

        //MessageHandlerRegistration message_handler_tx_progress {                     // MessageHandlerRegistration class which relays 
        //    Message::ID::TXProgress,                                                 // Message::ID::TXProgress messages to your app 
        //    [this](const Message* const p) {                                         // code from baseband. The Ternary Operator passes   
        //        const auto message = *reinterpret_cast<const TXProgressMessage*>(p); // an uint32_t progressvalue and a bool stating if  
        //        this->on_tx_progress(message.progress, message.done);                // TX progress has be complete.
        //    }};

        MessageHandlerRegistration message_handler_frame_sync{
            Message::ID::DisplayFrameSync,
            [this](const Message* const) {
                this->on_timer();
            }};
    };

    class CactusTestView : public View                                // App class declaration
    {
    public:
        CactusTestView(NavigationView &nav, Rect parent_rect);
        CactusTestView(const CactusTestView&) = delete;
        CactusTestView(CactusTestView&&) = delete;
        CactusTestView& operator=(const CactusTestView&) = delete;
        CactusTestView& operator=(CactusTestView&&) = delete;
        ~CactusTestView();
        void focus() override;

    private:
        Button button_a{{0 * 8, 1 * 16, 6 * 8, 16 + 8}, "A"};
        Button button_b{{8 * 8, 1 * 16, 6 * 8, 16 + 8}, "B"};
        Button button_c{{16 * 8, 1 * 16, 6 * 8, 16 + 8}, "C"};
        Button button_d{{24 * 8, 1 * 16, 6 * 8, 16 + 8}, "D"};
        Button button_e{{0 * 8, 3 * 16, 6 * 8, 16 + 8}, "E"};
        Button button_f{{8 * 8, 3 * 16, 6 * 8, 16 + 8}, "F"};
        Button button_g{{16 * 8, 3 * 16, 6 * 8, 16 + 8}, "G"};
        Button button_h{{24 * 8, 3 * 16, 6 * 8, 16 + 8}, "H"};
    /*
        Button button_I{{0 * 8, 15 * 16, 6 * 8, 16 + 8}, "I"};
        Button button_J{{8 * 8, 15 * 16, 6 * 8, 16 + 8}, "J"};
        Button button_K{{16 * 8, 15 * 16, 6 * 8, 16 + 8}, "K"};
        Button button_L{{24 * 8, 15 * 16, 6 * 8, 16 + 8}, "L"};
        Button button_M{{0 * 8, 17 * 16, 6 * 8, 16 + 8}, "M"};
        Button button_N{{8 * 8, 17 * 16, 6 * 8, 16 + 8}, "N"};
        Button button_O{{16 * 8, 17 * 16, 6 * 8, 16 + 8}, "O"};
        Button button_P{{24 * 8, 17 * 16, 6 * 8, 16 + 8}, "P"};
    */
        Button button_all{{4 * 8, 11 * 16, 8 * 8, 16 + 16}, "ALL ON"};
        Button button_off{{16 * 8, 11 * 16, 8 * 8, 16 + 16}, "ALL OFF"};
    //bool allow_tx = false;
    Thread* testthread{nullptr};
    void on_hide();
    void test(int i);
    void terminate_test();
    };

    class CactusDbgView : public View                                // App class declaration
    {
    public:
        CactusDbgView(NavigationView &nav, Rect parent_rect);
        CactusDbgView(const CactusDbgView&) = delete;
        CactusDbgView(CactusDbgView&&) = delete;
        CactusDbgView& operator=(const CactusDbgView&) = delete;
        CactusDbgView& operator=(CactusDbgView&&) = delete;
        ~CactusDbgView();
        void focus() override;

    private:
        Labels labels{
            {{0 * 8, 2 * 16}, "trunk1:", Theme::getInstance()->fg_light->foreground},
            {{16 * 8, 2 * 16}, "trunk2:", Theme::getInstance()->fg_light->foreground},
            {{0 * 8, 4 * 16}, "trunk3:", Theme::getInstance()->fg_light->foreground},
            {{16 * 8, 4 * 16}, "trunk4:", Theme::getInstance()->fg_light->foreground},
            {{0 * 8, 6 * 16}, "trunk5:", Theme::getInstance()->fg_light->foreground},
            {{16 * 8, 6 * 16}, "trunk6:", Theme::getInstance()->fg_light->foreground},};

        NumberField trunk1_nf{
            {8 * 8, 2 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        NumberField trunk2_nf{
            {24 * 8, 2 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        NumberField trunk3_nf{
            {8 * 8, 4 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        NumberField trunk4_nf{
            {24 * 8, 4 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        NumberField trunk5_nf{
            {8 * 8, 6 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        NumberField trunk6_nf{
            {24 * 8, 6 * 16},
            3,
            {0, 255},
            1,
            ' ',
            true};

        Button button_send{{72, 160, 96, 48}, "SEND"};

        uint8_t trunk1_v{0};
        uint8_t trunk2_v{255};
        uint8_t trunk3_v{255};
        uint8_t trunk4_v{255};
        uint8_t trunk5_v{0};
        uint8_t trunk6_v{0};

        //bool allow_tx = false;
        Thread* testthread{nullptr};
        void on_hide();
        void send_code();
    };

    class CactusView : public View                                // App class declaration
    {
    public:
        CactusView(NavigationView &nav);                          // App class init function declaration
        ~CactusView();
        std::string title() const override { return "Cactus"; }; // App title

        void focus() override;

    private:
        NavigationView& nav_;

        Rect view_rect = {0, 28, 240, 228};

        CactusTxView view_tx{nav_, view_rect};
        CactusTestView view_test{nav_, view_rect};
        CactusDbgView view_dbg{nav_, view_rect};

        TabView tab_view{
            {"TX", Theme::getInstance()->fg_cyan->foreground, &view_tx},
            {"test", Theme::getInstance()->fg_green->foreground, &view_test},
            {"debug", Theme::getInstance()->fg_green->foreground, &view_dbg},
        };
        TransmitterView2 tx_view2{
            {48, 264},
            false
        };
    };
}