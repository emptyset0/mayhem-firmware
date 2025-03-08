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
            {{20 * 8, 4 * 8}, "ms", Theme::getInstance()->fg_light->foreground},};

        NumberField interval_nf{
            {16 * 8, 4 * 8},
            5,
            {2000, 20000},
            100,
            ' '};

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
    //bool allow_tx = false;
    Thread* testthread{nullptr};
    void on_hide();
    void test(int i);
    void terminate_test();
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

        TabView tab_view{
            {"TX", Theme::getInstance()->fg_cyan->foreground, &view_tx},
            {"test", Theme::getInstance()->fg_green->foreground, &view_test},
        };
        TransmitterView2 tx_view2{
            {48, 264},
            false
        };
    };
}