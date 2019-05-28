open Types;
let str = React.string;

type state = {questions: list(Question.t)};

type actions =
  | AddQuestion
  | AddOption(string)
  | ChangeQuestionTitle(string, string)
  | ChangeQuestionOption(string, string, string)
  | SaveQuiz;

let mockQuestions: list(Question.t) = [
  {
    id: "1",
    title: "What is your favorite color?",
    options: [
      {id: "1", title: "Blue", isCorrect: false},
      {id: "2", title: "Red", isCorrect: true},
      {id: "3", title: "Green", isCorrect: false},
      {id: "4", title: "Yellow", isCorrect: false},
    ],
  },
];

let quizReducer = (state, action) =>
  switch (action) {
  | AddQuestion => {questions: Question.appendEmpty(state.questions)}
  | AddOption(questionID) => {
      questions:
        List.map(
          (question: Question.t) =>
            if (questionID == question.title) {
              Question.{
                id: question.id,
                title: question.title,
                options: QuestionOption.appendEmpty(question.options),
              };
            } else {
              question;
            },
          state.questions,
        ),
    }
  | ChangeQuestionTitle(questionID, title) => {
      questions:
        List.map(
          (question: Question.t) =>
            questionID == question.id
              ? Question.{id: question.id, title, options: question.options}
              : question,
          state.questions,
        ),
    }
  | ChangeQuestionOption(questionID, optionID, title) => {
      questions:
        List.map(
          (question: Question.t) =>
            if (questionID == question.id) {
              Question.{
                id: question.id,
                title: question.title,
                options:
                  List.map(
                    (option: QuestionOption.t) =>
                      optionID == option.id
                        ? {
                          id: option.id,
                          title,
                          QuestionOption.isCorrect: false,
                        }
                        : option,
                    question.options,
                  ),
              };
            } else {
              question;
            },
          state.questions,
        ),
    }
  | SaveQuiz =>
    Js.log("SaveQuiz");
    state;
  };

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(quizReducer, {questions: mockQuestions});

  let onAddOption = id => dispatch(AddOption(id));

  let onChangeQuestionTitle = (id, title) =>
    dispatch(ChangeQuestionTitle(id, title));

  let onChangeQuestionOption = (questionID, optionID, title) =>
    dispatch(ChangeQuestionOption(questionID, optionID, title));

  let renderQuestions =
    state.questions
    |> List.map(question =>
         <QuestionComposer
           key={question.id}
           question
           onAddOption
           onChangeQuestionTitle
           onChangeQuestionOption
         />
       )
    |> Array.of_list
    |> React.array;

  <main className="mt-8 container mx-auto">
    <header className="text-center">
      <Text.Heading> "A Reasonable Quiz" </Text.Heading>
      <Text> "Create a quiz built of radio questions" </Text>
    </header>
    <Form
      onSubmit={e => {
        ReactEvent.Form.preventDefault(e);
        dispatch(SaveQuiz);
      }}>
      <div className="mb-8"> renderQuestions </div>
      <footer className="flex items-center justify-between">
        <Button
          title="Add Question"
          intent=Button.Secondary
          onClick={_e => dispatch(AddQuestion)}
        />
        <Button title="Save" type_="submit" intent=Button.Primary />
      </footer>
    </Form>
  </main>;
};