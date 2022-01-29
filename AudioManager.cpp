#include "Headers.h"
const char* AudioManager::music[14] = {
	"Data\\Music\\Background.mp3",
	"Data\\Music\\BallBlockCollision.wav",
	"Data\\Music\\BallBoardCollision.wav",
	"Data\\Music\\BallWallCollision.wav",
	"Data\\Music\\BallBrickCollision.wav",
	"Data\\Music\\BallBombCollision.wav",
	"Data\\Music\\GameOver.wav",
	"Data\\Music\\LevelUp.wav",
	"Data\\Music\\Button.wav",
	"Data\\Music\\Button2.wav",
	"Data\\Music\\Reload.wav",
	"Data\\Music\\Gun.wav",
	"Data\\Music\\CatchItem.wav",
	"Data\\Music\\PowerUp.wav"
};
ISoundEngine *AudioManager::soundEngine = createIrrKlangDevice();
AudioManager::AudioManager()
{

}
AudioManager::~AudioManager()
{
	soundEngine->drop();	// Delete soundengine
}
void AudioManager::play(musicType type, bool loop)		// If loop==true , then the audio will play again and again
{
	soundEngine->play2D(music[type], loop);		// Play an audio
}
void AudioManager::play(const char *filename,bool loop)		// If loop==true , then the audio will play again and again
{
	soundEngine->play2D(filename,loop);		// Play an audio
}
void AudioManager::stopAll()
{
	soundEngine->stopAllSounds();	// Stop all sounspeed
}
