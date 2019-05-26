type questionOption = {
  title: string,
  isCorrect: bool,
};

type t = {
  title: string,
  options: list(questionOption),
};