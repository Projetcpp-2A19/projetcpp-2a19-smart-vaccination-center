from record_and_transcribe import record_and_transcribe

if __name__ == "__main__":
    text = record_and_transcribe()
    print(text.encode("utf-8").decode("utf-8"))
