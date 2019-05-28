module QuestionOption = {
  type t = {
    id: string,
    title: string,
    isCorrect: bool,
  };

  let makeEmpty = (~title="", ~isCorrect=false, id) => {
    id,
    title,
    isCorrect,
  };

  let appendEmpty = options => {
    let newOption = makeEmpty(string_of_int(List.length(options) + 1));
    options @ [newOption];
  };
};

module Question = {
  type t = {
    id: string,
    title: string,
    options: list(QuestionOption.t),
  };

  let makeEmpty = (~title="", ~options=[], id) => {id, title, options};

  let appendEmpty = questions => {
    let newQuestion = makeEmpty(string_of_int(List.length(questions) + 1));
    questions @ [newQuestion];
  };
};