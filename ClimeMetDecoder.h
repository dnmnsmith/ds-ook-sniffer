/* ===================================================
 * ClimeMetDecoder.h
 * ---------------------------------------------------
 * 433 Mhz decoding OoK frame from Climemet
 *
 *  Created on: 16 March 2015
 *  Author: Duncan Smith based on work by Dominique Pierre and Suat �zg�r.
 *
 *	 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 	 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 	 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 	 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 	 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * 	 THE SOFTWARE.
 * ===================================================
 */

#ifndef CLIMEMET_DECODER_INCLUDED
#define CLIMEMET_DECODER_INCLUDED

#include <stdint.h>

#include "RcOok.h"

class ClimeMetDecoder : public DecodeOOK {
public:
	ClimeMetDecoder();

 // Over-ride api 
    virtual int decode (word width);

    bool getTemperature( float &temp )const;
    bool getHumidity( int &humidity ) const;
    bool getDeviceCode( int &code ) const;
    
protected:
  // Carry out post-decode operations; verify checksum & sync bytes
  int finished();
    
  // Verify checksum
  int VerifyCheckSum() const;  
}; 

#endif // CLIMEMET_DECODER_INCLUDED
