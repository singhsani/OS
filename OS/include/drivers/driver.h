#ifndef __OS_DRIVERS__DRIVER_H
#define __OS_DRIVERS__DRIVER_H
namespace OS{
    namespace drivers{
        class Driver{
        public:
            Driver();
            ~Driver();
            virtual void Activate();
            virtual int Reset();
            virtual void DeActivate();
        };

        class DriverManager{
        private:
            Driver* driver[255];
            int numDrivers;
        public:
            DriverManager();
            ~DriverManager();
            void addDriver(Driver*);
            void ActivateAll();
        };
    }
}

#endif
