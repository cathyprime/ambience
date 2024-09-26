use rodio::{Decoder, OutputStream, Sink, Source};
use std::{fs::File, io::BufReader};
use std::sync::mpsc::Sender;

#[derive(Debug)]
pub(crate) enum MusakError {
	Buf(std::io::Error),
	Decoder(rodio::decoder::DecoderError),
	Play(rodio::PlayError),
	Stream(rodio::StreamError),
}

macro_rules! err_conv {
	($value:ty, $eq:ident) => {
		impl std::convert::From<$value> for MusakError {
			fn from(value: $value) -> Self {
				MusakError::$eq(value)
			}
		}
	};
}
err_conv!(std::io::Error, Buf);
err_conv!(rodio::decoder::DecoderError, Decoder);
err_conv!(rodio::PlayError, Play);
err_conv!(rodio::StreamError, Stream);

impl std::fmt::Display for MusakError {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
		write!(
			f,
			"{}",
			match self {
				MusakError::Buf(x) => x.to_string(),
				MusakError::Decoder(x) => x.to_string(),
				MusakError::Play(x) => x.to_string(),
				MusakError::Stream(x) => x.to_string(),
			}
		)
	}
}

pub(crate) fn musak(tx: Sender<Result<(), MusakError>>) {
    tx.send(m_musak()).unwrap();
}

fn m_musak() -> Result<(), MusakError> {
	let (_stream, stream_handle) = OutputStream::try_default()?;
	let sink = Sink::try_new(&stream_handle)?;
	let sink2 = Sink::try_new(&stream_handle)?;

	let stream_source = {
		let stream = BufReader::new(File::open("assets/stream.ogg")?);
		Decoder::new_looped(stream)?
			.repeat_infinite()
	};

	let birds_source = {
		let birds = BufReader::new(File::open("assets/birds.ogg")?);
		Decoder::new_looped(birds)?
			.repeat_infinite()
	};

	sink.set_volume(0.2);
	sink2.set_volume(0.2);
	sink.append(stream_source);
	sink2.append(birds_source);

	sink.sleep_until_end();
	sink2.sleep_until_end();

	Ok(())
}
