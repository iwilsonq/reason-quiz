let str = React.string;

type state = {questions: list(Question.t)};

type actions =
  | AddQuestion
  | AddOption(string)
  | ChangeQuestionTitle(string, string)
  | ChangeQuestionOption(string, string, string);

let mockQuestions: list(Question.t) = [
  {
    title: "What is your favorite color?",
    options: [
      {title: "Blue", isCorrect: false},
      {title: "Red", isCorrect: true},
      {title: "Green", isCorrect: false},
      {title: "Yellow", isCorrect: false},
    ],
  },
];

let quizReducer = (state, action) =>
  switch (action) {
  | AddQuestion => {questions: state.questions @ [{title: "", options: []}]}
  | AddOption(id) => {
      questions:
        List.map(
          (question: Question.t) =>
            if (id == question.title) {
              {
                Question.title: question.title,
                options: question.options @ [{title: "", isCorrect: false}],
              };
            } else {
              question;
            },
          state.questions,
        ),
    }
  | ChangeQuestionTitle(id, title) => {
      questions:
        List.map(
          (question: Question.t) =>
            if (id == question.title) {
              {Question.title, options: question.options};
            } else {
              question;
            },
          state.questions,
        ),
    }
  | ChangeQuestionOption(questionID, optionID, title) => {
      questions:
        List.map(
          (question: Question.t) =>
            if (questionID == question.title) {
              {
                Question.title: question.title,
                options:
                  List.map((option: Question.questionOption) =>
                    if (optionID == option.title) {
                      {Question.questionOption.title: title, isCorrect: false};
                    } else {
                      option;
                    }
                  ),
              };
            } else {
              question;
            },
          state.questions,
        ),
    }
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(quizReducer, {questions: []});

  let onAddOption = id => dispatch(AddOption(id));

  let onChangeQuestionTitle = (id, title) =>
    dispatch(ChangeQuestionTitle(id, title));

  let onChangeQuestionOption = (questionID, optionID, title) =>
    dispatch(ChangeQuestionOption(questionID, optionID, title));

  let renderQuestions =
    state.questions
    |> List.map(question =>
         <QuestionComposer
           question
           onAddOption
           onChangeQuestionTitle
           onChangeQuestionOption
         />
       )
    |> Array.of_list
    |> React.array;

  <main>
    <h1> {str("A Simple Quiz")} </h1>
    <p> {str("Create a quiz built of radio questions")} </p>
    renderQuestions
    <button onClick={_e => dispatch(AddQuestion)}>
      {"Add Question" |> str}
    </button>
  </main>;
};