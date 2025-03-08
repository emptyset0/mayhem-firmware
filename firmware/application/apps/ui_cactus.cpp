#include "ui_cactus.hpp"
#include "encoders.hpp"
#include "baseband_api.hpp"

#include <cstdlib>
#include <cstring>
#include <bitset>
//#include <chrono>

using namespace portapack;

namespace ui
{
    //const std::bitset<97> lock("1110100010001110100011101000111010001000100010001000111010001110111010001110111010001000111010001");
    //const std::bitset<97> unlock("1110100010001110100011101000111010001000100010001000111010001110111010001110111010001000100011101");
    //const std::bitset<97> start("1110100010001110100011101000111010001000100010001000111010001110111010001110111010001110100010001");
    //const std::bitset<97> warning("1110100010001110100011101000111010001000100010001000111010001110111010001110111011101000100010001");

    class bitset_tx {
    public:
        bitset_tx(const std::bitset<56>& bits) :
            in(bits) {}
        const std::string tx_string() const{
            std::bitset<56 * 3> result;
            const std::bitset<56 * 3> in_extended{ in.to_ullong() };
            const std::bitset<56 * 3> prefix_extended{ 0b010 };
            const std::bitset<56 * 3> one_extended{ 0b1 };
            for (int i = 56 - 1; i > 0 - 1; i--) {
                result |= (((in_extended >> i) & one_extended) | prefix_extended) << i * 3;
            }
            return lead.to_string() + result.to_string();
        }
    private:
        const std::bitset<56> in;
        const std::bitset<20> lead{ 0b00011111111000011110 };
    };

    struct light_codes {
    public:
        const bitset_tx red, green, blue, white, yellow, slow, medium, fast, steady, off, compl_off;
        light_codes(const std::bitset<56> in[11]) :
            red(in[0]), green(in[1]), blue(in[2]), white(in[3]), yellow(in[4]), slow(in[5]),
            medium(in[6]), fast(in[7]), steady(in[8]), off(in[9]), compl_off(in[10]) {}
    };

    const light_codes light_all(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000111111111111111111111111000000010000000010010100,
            0b00000000111111111111111111111111000000010000000110010101,
            0b00000000111111111111111111111111000000010000001010010110,
            0b00000000111111111111111111111111000000010000010010011000,
            0b00000000111111111111111111111111000000010000010110011001,
            0b00000000111111111111111111111111001000101010101001011111,
            0b00000000111111111111111111111111001000111010101001100000,
            0b00000000111111111111111111111111001001001010101001100001,
            0b00000000111111111111111111111111000000011010101000111110,
            0b00000000111111111111111111111111000000001010101000111101,
            0b00000000000000000000000000000000000000000000000000000000
        }
    );

    const light_codes light_a(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000000000010000000011111111000000010000000010010111,
            0b00000000000000010000000011111111000000010000000110011000,
            0b00000000000000010000000011111111000000010000001010011001,
            0b00000000000000010000000011111111000000010000010010011011,
            0b00000000000000010000000011111111000000010000010110011100,
            0b00000000000000010000000011111111001000101010101001100010,
            0b00000000000000010000000011111111001000111010101001100011,
            0b00000000000000010000000011111111001001001010101001100100,
            0b00000000000000010000000011111111000000011010101001000001,
            0b00000000000000010000000011111111000000001010101001000000,
            0b00000000111111101111111111111111000000001010101000111100
        }
    );

    const light_codes light_b(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000000000100000000011111111000000010000000010011000,
            0b00000000000000100000000011111111000000010000000110011001,
            0b00000000000000100000000011111111000000010000001010011010,
            0b00000000000000100000000011111111000000010000010010011100,
            0b00000000000000100000000011111111000000010000010110011101,
            0b00000000000000100000000011111111001000101010101001100011,
            0b00000000000000100000000011111111001000111010101001100100,
            0b00000000000000100000000011111111001001001010101001100101,
            0b00000000000000100000000011111111000000011010101001000010,
            0b00000000000000100000000011111111000000001010101001000001,
            0b00000000111111011111111111111111000000001010101000111011
        }
    );

    const light_codes light_c(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000000001000000000011111111000000010000000010011010,
            0b00000000000001000000000011111111000000010000000110011011,
            0b00000000000001000000000011111111000000010000001010011100,
            0b00000000000001000000000011111111000000010000010010011110,
            0b00000000000001000000000011111111000000010000010110011111,
            0b00000000000001000000000011111111001000101010101001100101,
            0b00000000000001000000000011111111001000111010101001100110,
            0b00000000000001000000000011111111001001001010101001100111,
            0b00000000000001000000000011111111000000011010101001000100,
            0b00000000000001000000000011111111000000001010101001000011,
            0b00000000111110111111111111111111000000001010101000111001
        }
    );

    const light_codes light_d(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000000010000000000011111111000000010000000010011110,
            0b00000000000010000000000011111111000000010000000110011111,
            0b00000000000010000000000011111111000000010000001010100000,
            0b00000000000010000000000011111111000000010000010010100010,
            0b00000000000010000000000011111111000000010000010110100011,
            0b00000000000010000000000011111111001000101010101001101001,
            0b00000000000010000000000011111111001000111010101001101010,
            0b00000000000010000000000011111111001001001010101001101011,
            0b00000000000010000000000011111111000000011010101001001000,
            0b00000000000010000000000011111111000000001010101001000111,
            0b00000000111101111111111111111111000000001010101000110101
        }
    );

    const light_codes light_e(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000000100000000000011111111000000010000000010100110,
            0b00000000000100000000000011111111000000010000000110100111,
            0b00000000000100000000000011111111000000010000001010101000,
            0b00000000000100000000000011111111000000010000010010101010,
            0b00000000000100000000000011111111000000010000010110101011,
            0b00000000000100000000000011111111001000101010101001110001,
            0b00000000000100000000000011111111001000111010101001110010,
            0b00000000000100000000000011111111001001001010101001110011,
            0b00000000000100000000000011111111000000011010101001010000,
            0b00000000000100000000000011111111000000001010101001001111,
            0b00000000111011111111111111111111000000001010101000101101
        }
    );

    const light_codes light_f(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000001000000000000011111111000000010000000010110110,
            0b00000000001000000000000011111111000000010000000110110111,
            0b00000000001000000000000011111111000000010000001010111000,
            0b00000000001000000000000011111111000000010000010010111010,
            0b00000000001000000000000011111111000000010000010110111011,
            0b00000000001000000000000011111111001000101010101010000001,
            0b00000000001000000000000011111111001000111010101010000010,
            0b00000000001000000000000011111111001001001010101010000011,
            0b00000000001000000000000011111111000000011010101001100000,
            0b00000000001000000000000011111111000000001010101001011111,
            0b00000000110111111111111111111111000000001010101000011101
        }
    );

    const light_codes light_g(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000010000000000000011111111000000010000000011010110,
            0b00000000010000000000000011111111000000010000000111010111,
            0b00000000010000000000000011111111000000010000001011011000,
            0b00000000010000000000000011111111000000010000010011011010,
            0b00000000010000000000000011111111000000010000010111011011,
            0b00000000010000000000000011111111001000101010101010100001,
            0b00000000010000000000000011111111001000111010101010100010,
            0b00000000010000000000000011111111001001001010101010100011,
            0b00000000010000000000000011111111000000011010101010000000,
            0b00000000010000000000000011111111000000001010101001111111,
            0b00000000101111111111111111111111000000001010101011111101
        }
    );

    const light_codes light_h(
        (std::bitset<56>*) (const std::bitset<56>[11])
        {
            0b00000000100000000000000011111111000000010000000000010110,
            0b00000000100000000000000011111111000000010000000100010111,
            0b00000000100000000000000011111111000000010000001000011000,
            0b00000000100000000000000011111111000000010000010000011010,
            0b00000000100000000000000011111111000000010000010100011011,
            0b00000000100000000000000011111111001000101010101011100001,
            0b00000000100000000000000011111111001000111010101011100010,
            0b00000000100000000000000011111111001001001010101011100011,
            0b00000000100000000000000011111111000000011010101011000000,
            0b00000000100000000000000011111111000000001010101010111111,
            0b00000000011111111111111111111111000000001010101010111101
        }
    );

    const light_codes lights[8] = {light_a, light_b, light_c, light_d, light_e, light_f, light_g, light_h};

    //CactusTxView::CactusTxView(NavigationView &nav) // Application Main
    //{
    //    // App code
    //}

    //void CactusTxView::update()                   // Every time you get a DisplayFrameSync message this function will be ran
    //{
        // Message code
    //}

#define OOK_SAMPLERATE 2000000U

    void start_tx(std::string& message)              // Message input as "101101"
    {
        size_t bitstream_length = encoders::make_bitstream(message);       // Function from encoders.hpp. Encodes then 
                                                                  // sets message to TX data pointer via... 	
                                                                  // uint8_t * bitstream = shared_memory.bb_data.data; 
                                                                  // on line 34 of encoders.cpp and returns length. 

        transmitter_model.set_target_frequency(433920000);       // Center frequency in hz
        transmitter_model.set_sampling_rate(OOK_SAMPLERATE);     // (2280000) Value from encoders.hpp
        //transmitter_model.set_tx_gain(24);
        //transmitter_model.set_rf_amp(false);                      // RF amp on
        transmitter_model.set_baseband_bandwidth(2000000);       // Bandwidth
        transmitter_model.enable();                              // Radio enable

        baseband::set_ook_data(                                  // ASK/OOK TX function
            bitstream_length,                                    // Length of message
            OOK_SAMPLERATE / 3936, //2500, //1766,                               // Symble period (560us), Sample Rate / Baud 
            4,                                                   // Repeat transmissions
            0 //100                                                  // Pause symbles
        );
    }

    void stop_tx()                                    // Stop TX function
    {
        baseband::kill_ook();
        transmitter_model.disable();                              // Disable transmitter_model

        // Add UI logic to let the user know the TX has stoped 
    } 

    void send_msg(const std::string& message)
    {
        std::string msg = message;
        start_tx(msg);
    }

    int gen_rand(int x)
    {
        std::srand(LPC_RTC->CTIME0);
        return std::rand() / ((RAND_MAX + 1u) / x);
    }

    static msg_t testthread_fn(void* arg){
        int i = (int) arg;
        send_msg(lights[i].white.tx_string() + lights[i].compl_off.tx_string());
        chThdExit(0);
        return 0;
    }

    static msg_t loopthread_fn(void* arg)
    {
        CactusTxView* arg_c = (CactusTxView*)arg;
        Painter painter;
        //for (int i=0; i<10; i++)
        //{   
        //    if (chThdShouldTerminate()) break;
        //    std::string s = std::to_string(gen_rand(8));
        //    painter.draw_string({100, 160}, *Theme::getInstance()->bg_darkest, s);
        //    chThdSleepMilliseconds(100);
        //}
        //chThdExit(0);
        //return 0;
        /*
        int phase = 2;
        int current = 0;
        auto time_prev = std::chrono::system_clock::now();
        auto time_now = std::chrono::system_clock::now();
        int elapsed = 1000000;
        int i = 0;
        while (true)
        {
            if (chThdShouldTerminate()) break;
            time_now = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_prev).count();
            if (phase == 0)
            {
                current = gen_rand(8);
                arg_c->send_msg(lights[current].red.tx_string());
                // arg_c->send_msg(lights[current].steady.tx_string());
                arg_c->send_msg(lights[current].compl_off.tx_string());
                phase += 1;
            }
            else if (phase == 1 && elapsed >= arg_c->interval * 0.667)
            {
                arg_c->send_msg(lights[current].medium.tx_string());
                phase += 1;
            }
            else if (phase == 2 && elapsed >= arg_c->interval)
            {
                time_prev = std::chrono::system_clock::now();
                arg_c->send_msg(light_all.green.tx_string());
                arg_c->send_msg(light_all.steady.tx_string());
                phase += 1;
            }
            else if (phase == 3 && elapsed >= 1000)
            {
                time_prev = std::chrono::system_clock::now();
                phase = 0;
            }
            else
            {
                chThdSleepMilliseconds(100);
            }
            painter.draw_string({100, 180}, *Theme::getInstance()->bg_darkest, std::to_string(elapsed));
            painter.draw_string({100, 160}, *Theme::getInstance()->bg_darkest, std::to_string(phase));
            i++;
            painter.draw_string({100, 140}, *Theme::getInstance()->bg_darkest, std::to_string(i));
        }
        chThdExit(0);
        return 0;
        */
        int phase = 2;
        int current = 0;
        long long time_prev = -1000000;
        long long time_now = 0;
        double elapsed = 0;
        int i = 0;
        while (true)
        {
            if (chThdShouldTerminate()) break;
            time_now = arg_c->timer_scr;
            elapsed = (time_now - time_prev) / 60 * 1000;
            if (phase == 0)
            {
                current = gen_rand(8);
                send_msg(lights[current].red.tx_string() 
                + lights[current].compl_off.tx_string()
                + lights[current].medium.tx_string());
                phase += 1;
            }
            else if (phase == 1 && elapsed >= arg_c->interval * 0.667)
            {
                send_msg(lights[current].fast.tx_string());
                phase += 1;
            }
            else if (phase == 2 && elapsed >= arg_c->interval)
            {
                time_prev = arg_c->timer_scr;
                send_msg(light_all.green.tx_string());
                phase += 1;
            }
            else if (phase == 3 && elapsed >= 1000)
            {
                time_prev = arg_c->timer_scr;
                phase = 0;
            }
            else
            {
                chThdSleepMilliseconds(100);
            }
            //painter.draw_string({100, 80}, *Theme::getInstance()->bg_darkest, std::to_string(std::llround(elapsed)));
            painter.draw_string({100, 60}, *Theme::getInstance()->bg_darkest, std::to_string(phase));
            i++;
            painter.draw_string({100, 40}, *Theme::getInstance()->bg_darkest, std::to_string(i));
        }
        chThdExit(0);
        return 0;
    }

    CactusTxView::CactusTxView(NavigationView &nav, Rect parent_rect)                   // Application Main
    {
        set_parent_rect(parent_rect);
        hidden(true);
        //baseband::run_image(portapack::spi_flash::image_tag_ook); // M4 processor is being told to run proc_ook.cpp
                                                                  // found in the firmware/baseband/ folder. M4 is 
                                                                  // then reset after this command.
        // UI widget logic and calls to
        // start_tx() goes here.

        add_children({//&tab_view,
            //&view_config,
            //&view_scan,
            //&text_status,
            //&progressbar,
            &labels,
            &interval_nf,
            //&button_1,
            //&button_2,
            //&button_3,
            &button_start,
            //&tx_view,
            });

        //button_1.on_select = [this](const ui::Button&) {
        //    send_msg(lock.to_string());
        //};

        //button_2.on_select = [this](const ui::Button&) {
        //    send_msg(unlock.to_string());
        //};

        //button_3.on_select = [this](const ui::Button&) {
        //    send_msg(start.to_string());
        //    //loop();
        //};

        button_start.on_select = [this](const ui::Button&) {
            if (looping_) {
                set_looping(false);
                terminate_loop();
            }
            else {
                set_looping(true);
                terminate_loop();
                loopthread = chThdCreateFromHeap(NULL, 1024, NORMALPRIO, loopthread_fn, this);
            }    
        };

        interval_nf.on_change = [this](int32_t v) {
            interval = v;
        };

        //tx_view.on_edit_frequency = [this, &nav]() {
        //    auto new_view = nav.push<FrequencyKeypadView>(transmitter_model.target_frequency());
        //    new_view->on_changed = [this](rf::Frequency f) {
        //        transmitter_model.set_target_frequency(f);
        //    };
        //};

        //tx_view.on_start = [this]() {
        //    tx_view.set_transmitting(true);
        //    //start_tx(tab_view.selected());
        //    terminate_loop();
        //    loopthread = chThdCreateFromHeap(NULL, 1024, NORMALPRIO, loopthread_fn, this);
        //};

        //tx_view.on_stop = [this]() {
        //    tx_view.set_transmitting(false);
        //    terminate_loop();
        //    stop_tx();
        //};
        set_looping(false);
        interval_nf.set_value(interval);
    }

    CactusTxView::~CactusTxView() {
        terminate_loop();
        transmitter_model.disable();
        //baseband::shutdown();
    }

    void CactusTxView::focus() {
        interval_nf.focus();
    }

    void CactusTxView::on_hide() {
        terminate_loop();
        stop_tx();
        //tx_view.set_transmitting(false);
        set_looping(false);
    }

    void CactusTxView::set_looping(const bool looping) {
        if (looping) {
            button_start.set_text("STOP");
            button_start.set_style(&style_stop);
        } else {
            button_start.set_text("START");
            button_start.set_style(&style_start);
        }

        looping_ = looping;
    }

    //void CactusTxView::on_tx_progress(const uint32_t progress, const bool done)  // Function logic for when the message handler       
    //{                                                                          // sends a TXProgressMessage.
    //    if(done) {
    //        stop_tx();
    //        //tx_view.set_transmitting(false);
    //    } else {
    //        // UI logic, update ProgressBar with progress var
    //    }
    //}

    // called each 1/60th of second, so 6 = 100ms
    void CactusTxView::on_timer() {
        timer_scr += 1;
    }

    void CactusTxView::terminate_loop() {
        if (loopthread) {
            chThdTerminate(loopthread);
            chThdWait(loopthread);
            loopthread = nullptr;
        }
    }

    CactusTestView::CactusTestView(NavigationView &nav, Rect parent_rect)
    {
        set_parent_rect(parent_rect);
        hidden(true);

        add_children({&button_a,
                    &button_b,
                    &button_c,
                    &button_d,
                    &button_e,
                    &button_f,
                    &button_g,
                    &button_h,
                    });

    button_a.on_select = [this](const ui::Button&) {
            test(0);
        };

    button_b.on_select = [this](const ui::Button&) {
            test(1);
        };

    button_c.on_select = [this](const ui::Button&) {
            test(2);
        };

    button_d.on_select = [this](const ui::Button&) {
            test(3);
        };

    button_e.on_select = [this](const ui::Button&) {
            test(4);
        };

    button_f.on_select = [this](const ui::Button&) {
            test(5);
        };

    button_g.on_select = [this](const ui::Button&) {
            test(6);
        };
    
    button_h.on_select = [this](const ui::Button&) {
            test(7);
        };
    }

    CactusTestView::~CactusTestView() {
        terminate_test();
        transmitter_model.disable();
    }

    void CactusTestView::focus() {
        button_a.focus();
    }

    void CactusTestView::test(int i) {
        terminate_test();
        testthread = chThdCreateFromHeap(NULL, 1024, NORMALPRIO, testthread_fn, (void*) i);
    }
    void CactusTestView::terminate_test() {
        if (testthread) {
            chThdTerminate(testthread);
            chThdWait(testthread);
            testthread = nullptr;
        }
    }

    void CactusTestView::on_hide() {
        terminate_test();
        stop_tx();
    }

    CactusView::CactusView(
        NavigationView& nav)
        : nav_{nav} {
        baseband::run_image(portapack::spi_flash::image_tag_ook);

        add_children({&tab_view,
                    &view_tx,
                    &view_test,
                    &tx_view2,
                    });
    }

    CactusView::~CactusView() {
        baseband::shutdown();
    }

    void CactusView::focus() {
        tab_view.focus();
    }
}