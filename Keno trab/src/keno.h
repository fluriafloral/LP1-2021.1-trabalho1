#ifndef KENO_H_INCLUDED
#define KENO_H_INCLUDED

#include <vector>
using std::begin;
using std::end;

// Código 2 - classe KenoBet
using number_type = unsigned short int; //<! data type for a keno hit.
using cash_type = float; //<! Defines the wage type in this application.
using set_of_numbers_type = std::vector< number_type >;

class KenoBet {
    public:
        //! Creates an empty Keno bet.
        KenoBet( ) : m_wage(0)
        { /* empty */ };

        /*! Adds a number to the spots only if the number is not already there.
            @param spot_ The number we wish to include in the bet.
            @return T if number chosen is successfully inserted; F otherwise. */
        bool add_number( number_type spot_ )
        {
            bool r = true;

            for (set_of_numbers_type::iterator it = m_spots.begin();it != m_spots.end(); it++)
            {
                if (spot_ == *it)
                {
                    r = false;
                }
            }

            if (r == true)
            {
                m_spots.push_back(spot_);
                return r;
            }
            else
            {
                return r;
            }

        }

        /*! Sets the amount of money the player is betting.
            @param wage_ The wage.
            @return True if we have a wage above zero; false otherwise. */
        bool set_wage( cash_type wage_ )
        {
            if (wage_ > 0)
            {
                m_wage = wage_;
                return true;
            }
            else
            {
                return false;
            }
        }

        //! Resets a bet to an empty state.
        void reset( void )
        {
            m_wage = 0;
            m_spots.clear();

        }

        /*! Retrieves the player's wage on this bet.
            @return The wage value. */
        cash_type get_wage( void ) const {return m_wage;}

        /*! Returns to the current number of spots in the player's bet.
            @return Number of spots present in the bet. */
        size_t size( void ) const {return m_spots.size();}

        /*! Determine how many spots match the hits passed as argument.
            @param hits_ List of hits randomly chosen by the computer.
            @return An vector with the list of hits. */
        set_of_numbers_type get_hits( const set_of_numbers_type & hits_ ) const
        {
            set_of_numbers_type right_h;
            for (auto it = hits_.begin();it != hits_.end();it++)
            {
                for (auto it_ = m_spots.begin();it_ != m_spots.end();it_++)
                {
                    if (*it == *it_){
                        right_h.push_back(*it);
                    }
                }
            }
            return right_h;
        }

        /*! Return a vector< spot_type > with the spots the player has picked so far.
            @return The vector< spot_type > with the player's spots picked so far. */
        set_of_numbers_type get_spots( void ) const {return m_spots;}

    private:
        set_of_numbers_type m_spots;  //<! The player's bet.
        cash_type m_wage;             //<! The player's wage
};

#endif // KENO_H_INCLUDED
