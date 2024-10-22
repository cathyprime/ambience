use std::{io::BufRead, path::PathBuf};

#[derive(Debug)]
pub(crate) enum Icon {
    Path(PathBuf),
    Name(String)
}

impl Icon {
    pub fn is_path(&self) -> bool {
        matches!(self, Icon::Path(_))
    }
}

impl From<&str> for Icon {
    fn from(value: &str) -> Self {
        let as_path: PathBuf = value.into();
        match as_path.try_exists() {
            Ok(_) => Self::Path(as_path),
            Err(_) => Self::Name(value.to_owned()),
        }
    }
}

#[derive(Debug)]
pub(crate) struct SoundRecord {
    name: String,
    path: PathBuf,
    icon: Icon
}

impl TryFrom<String> for SoundRecord {
    type Error = &'static str;

    fn try_from(value: String) -> Result<Self, Self::Error> {
        let record_line: Vec<_> = value.split(",").collect();
        if record_line.len() != 3 {
            return Err("too many commas, implement escaping!")
        }

        Ok(Self {
            name: record_line[0].to_owned(),
            path: record_line[1].into(),
            icon: record_line[2].into(),
        })
    }
}


#[derive(Debug)]
pub(crate) struct Sounds(Vec<SoundRecord>);

impl std::ops::Deref for Sounds {
    type Target = Vec<SoundRecord>;

    fn deref(&self) -> &Self::Target {
        &(self.0)
    }
}

impl Sounds {
    pub(crate) fn save_file(&self, path: impl Into<PathBuf>) -> Self {
        todo!()
    }

    pub(crate) fn read_file(path_like: impl Into<PathBuf>) -> Self {
        let path: PathBuf = path_like.into();
        let path = path.canonicalize().expect("path should be valid");
        let file = std::fs::File::open(path).expect("file should open");
        let buf_read = std::io::BufReader::new(file);

        let sounds = buf_read
            .lines()
            .skip(1)
            .map(|l| -> SoundRecord {
                match l {
                    Ok(v) => v.try_into().expect("time for proper csv parsing"),
                    Err(e) => panic!("os error: {}", e),
                }
            })
            .collect();
        Self(sounds)
    }
}

