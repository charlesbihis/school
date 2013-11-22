/*
Author: Charles Bihis
Website: www.charlesbihis.com
Contact: admin@charlesbihis.com


Please read this Source Code License Agreement carefully before using
the source code.

You agree to indemnify, hold harmless and defend the author from and
against any loss, damage, claims or lawsuits, including attorney's
fees that arise or result from your use or distribution of the source
code.
	
THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT
ANY TECHNICAL SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. ALSO, THERE IS NO WARRANTY OF
NON-INFRINGEMENT, TITLE OR QUIET ENJOYMENT. IN NO EVENT SHALL THE AUTHOR
OR ITS SUPPLIERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
	public:		
		// ***** Accessors ***** //
		static Character *ControlInstance();
		float GetRotateSpeed();
		float GetRotateSpeedOld();
		int GetFogStart();
		int GetFogEnd();
		
		// ***** Manipulators ***** //

		// ***** Mutators ***** //
		void Reset();
		void PauseRotation();
		void IncreaseRotateSpeed();
		void DecreaseRotateSpeed();
		void ToggleFog();
		void SetFogStart(int new_value);
		void IncreaseFogStart();
		void DecreaseFogStart();
		void SetFogEnd(int new_value);
		void IncreaseFogEnd();
		void DecreaseFogEnd();

	protected:
		Character();

	private:
		float rotate_speed;
		float rotate_speed_old;
		bool fog;
		int fog_start;
		int fog_end;
};  // class declaration

#endif