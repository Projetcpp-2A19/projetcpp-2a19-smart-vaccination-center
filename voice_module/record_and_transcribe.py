import sounddevice as sd
from scipy.io.wavfile import write
import whisper

def record_audio(filename="audio.wav", duration=10, fs=16000):
    #print("Recording...")
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype='int16')
    sd.wait()
    write(filename, fs, audio)
    #print("Saved to", filename)

def transcribe_audio(filename="audio.wav"):
    #print("Loading model...")
    model = whisper.load_model("base")
    #print("Transcribing...")
    result = model.transcribe(filename, language="fr")
    #print("Transcription:")
    #print(result["text"])
    return result["text"]

def record_and_transcribe():
    record_audio()
    return transcribe_audio()

